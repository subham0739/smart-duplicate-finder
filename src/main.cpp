#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;
using namespace std;

// Convert bytes into KB, MB, GB etc.
string formatSize(uintmax_t bytes)
{
    const char* units[] = {"B", "KB", "MB", "GB", "TB"};

    double size = static_cast<double>(bytes);
    int unit = 0;

    while (size >= 1024 && unit < 4)
    {
        size /= 1024;
        unit++;
    }

    stringstream output;
    output << fixed << setprecision(2) << size << " " << units[unit];

    return output.str();
}

// Compare two files byte by byte
bool areIdentical(const fs::path& file1, const fs::path& file2)
{
    ifstream a(file1, ios::binary);
    ifstream b(file2, ios::binary);

    if (!a || !b)
        return false;

    const size_t BUFFER_SIZE = 4096;

    char bufferA[BUFFER_SIZE];
    char bufferB[BUFFER_SIZE];

    while (true)
    {
        a.read(bufferA, BUFFER_SIZE);
        b.read(bufferB, BUFFER_SIZE);

        streamsize countA = a.gcount();
        streamsize countB = b.gcount();

        if (countA != countB)
            return false;

        for (streamsize i = 0; i < countA; i++)
        {
            if (bufferA[i] != bufferB[i])
                return false;
        }

        if (a.eof() && b.eof())
            return true;

        if (a.bad() || b.bad())
            return false;
    }
}

// Scan all files and group them by size
map<uintmax_t, vector<fs::path>> scanFiles(const fs::path& directory)
{
    map<uintmax_t, vector<fs::path>> filesBySize;

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(
                 directory,
                 fs::directory_options::skip_permission_denied))
        {
            try
            {
                if (!entry.is_regular_file())
                    continue;

                uintmax_t size = entry.file_size();

                filesBySize[size].push_back(entry.path());
            }
            catch (const fs::filesystem_error&)
            {
                // Ignore inaccessible files
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        cerr << "Error while scanning: " << e.what() << endl;
    }

    return filesBySize;
}

// Find duplicate groups
vector<vector<fs::path>>
findDuplicates(const map<uintmax_t, vector<fs::path>>& filesBySize)
{
    vector<vector<fs::path>> duplicateGroups;

    for (const auto& entry : filesBySize)
    {
        const auto& files = entry.second;

        // A single file cannot be a duplicate
        if (files.size() < 2)
            continue;

        vector<bool> checked(files.size(), false);

        for (size_t i = 0; i < files.size(); i++)
        {
            if (checked[i])
                continue;

            vector<fs::path> group;

            group.push_back(files[i]);
            checked[i] = true;

            for (size_t j = i + 1; j < files.size(); j++)
            {
                if (checked[j])
                    continue;

                if (areIdentical(files[i], files[j]))
                {
                    group.push_back(files[j]);
                    checked[j] = true;
                }
            }

            if (group.size() > 1)
                duplicateGroups.push_back(group);
        }
    }

    return duplicateGroups;
}

int main(int argc, char* argv[])
{
    cout << "\n";
    cout << "============================================\n";
    cout << "       SMART DUPLICATE FILE FINDER\n";
    cout << "============================================\n\n";

    // Check command-line argument
    if (argc != 2)
    {
        cout << "Usage:\n";
        cout << "  ./duplicate_finder <directory>\n\n";
        cout << "Example:\n";
        cout << "  ./duplicate_finder test_files\n";

        return 1;
    }

    fs::path directory = argv[1];

    // Check directory
    if (!fs::exists(directory))
    {
        cerr << "Error: Directory does not exist.\n";
        return 1;
    }

    if (!fs::is_directory(directory))
    {
        cerr << "Error: Path is not a directory.\n";
        return 1;
    }

    cout << "Scanning: " << fs::absolute(directory) << "\n\n";

    // Scan files
    auto filesBySize = scanFiles(directory);

    // Count files
    size_t totalFiles = 0;

    for (const auto& entry : filesBySize)
        totalFiles += entry.second.size();

    cout << "Files scanned: " << totalFiles << "\n\n";

    // Find duplicates
    auto duplicates = findDuplicates(filesBySize);

    if (duplicates.empty())
    {
        cout << "No duplicate files found.\n";
        cout << "\nScan completed successfully.\n";

        return 0;
    }

    uintmax_t recoverableSpace = 0;

    cout << "Duplicate Groups\n";
    cout << "--------------------------------------------\n";

    for (size_t i = 0; i < duplicates.size(); i++)
    {
        const auto& group = duplicates[i];

        uintmax_t fileSize = fs::file_size(group[0]);

        uintmax_t recoverable =
            fileSize * (group.size() - 1);

        recoverableSpace += recoverable;

        cout << "\nGroup " << i + 1 << "\n";

        for (size_t j = 0; j < group.size(); j++)
        {
            cout << "  " << j + 1 << ". "
                 << group[j] << "\n";
        }

        cout << "  File size: "
             << formatSize(fileSize) << "\n";

        cout << "  Recoverable: "
             << formatSize(recoverable) << "\n";
    }

    cout << "\n============================================\n";
    cout << "Total duplicate groups: "
         << duplicates.size() << "\n";

    cout << "Potentially recoverable space: "
         << formatSize(recoverableSpace) << "\n";

    cout << "============================================\n";

    cout << "\nScan completed successfully.\n";

    return 0;
}
