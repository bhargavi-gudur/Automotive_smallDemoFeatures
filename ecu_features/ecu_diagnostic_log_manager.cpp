/**
 * @file ecu_diagnostic_log_manager.cpp
 * @author Gandla Bhargavi
 * @brief
 *   Simulates an automotive ECU Diagnostic Log File Manager.
 *
 *   The system creates a diagnostic log directory,
 *   writes ECU fault information to a log file,
 *   checks whether the file exists, and displays
 *   basic file information.
 *
 *   Demonstrates:
 *   - Abstraction
 *   - Inheritance
 *   - Runtime Polymorphism
 *   - Encapsulation
 *   - STL filesystem
 *   - File handling
 *
 * @date 26-08-2026
 */

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
namespace fs = filesystem;

/**
 * @class ECU
 * @brief Abstract base class for an automotive ECU.
 */
class ECU
{
public:

    /**
     * @brief Manage ECU diagnostic logs.
     */
    virtual void processData() = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~ECU() = default;
};

/**
 * @class DiagnosticLogManager
 * @brief Manages ECU diagnostic log files.
 */
class DiagnosticLogManager : public ECU
{
private:

    /**
     * @brief Directory used for diagnostic logs.
     */
    fs::path logDirectory =
        "ecu_logs";

    /**
     * @brief Diagnostic log file.
     */
    fs::path logFile =
        logDirectory / "diagnostic_log.txt";

public:

    /**
     * @brief Create directory and diagnostic log.
     */
    void processData() override
    {
        cout << "===== ECU Diagnostic Log Manager =====\n";

        /*
         * Create the directory if it does not exist.
         */
        if(!fs::exists(logDirectory))
        {
            fs::create_directories(logDirectory);

            cout << "\nLog directory created: "
                 << logDirectory
                 << endl;
        }
        else
        {
            cout << "\nLog directory already exists.\n";
        }

        /*
         * Write diagnostic information.
         */
        ofstream outputFile(logFile);

        if(!outputFile)
        {
            cout << "Unable to create diagnostic log file.\n";
            return;
        }

        outputFile << "ECU Diagnostic Log\n";
        outputFile << "==================\n";
        outputFile << "P0300 - Engine Misfire Detected\n";
        outputFile << "P0420 - Catalyst Efficiency Warning\n";
        outputFile << "P0171 - System Too Lean\n";

        outputFile.close();

        cout << "Diagnostic log created successfully.\n";

        /*
         * Check whether the file exists.
         */
        if(fs::exists(logFile))
        {
            cout << "\nLog File Status: AVAILABLE\n";

            cout << "File Name: "
                 << logFile.filename()
                 << endl;

            cout << "File Size: "
                 << fs::file_size(logFile)
                 << " bytes"
                 << endl;
        }

        /*
         * Read the log file.
         */
        ifstream inputFile(logFile);

        if(!inputFile)
        {
            cout << "Unable to read diagnostic log.\n";
            return;
        }

        cout << "\n===== Diagnostic Log Contents =====\n";

        string line;

        while(getline(inputFile, line))
        {
            cout << line << endl;
        }

        inputFile.close();

        cout << "\nDiagnostic log processing completed.\n";
    }
};

/**
 * @brief Main function.
 *
 * Demonstrates runtime polymorphism using
 * a base-class pointer.
 */
int main()
{
    ECU* ecu =
        new DiagnosticLogManager();

    ecu->processData();

    delete ecu;

    return 0;
}