/**
 *  Challenge C++ AISDigital
 *
 *  @author Rafael Lima
 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

// CSV: File Format
// DBN,School Name,Number of Test Takers,Critical Reading Mean,Mathematics Mean,Writing Mean


/**
 * Read CSV File
 */
std::vector<std::string> readDatabaseFile(std::string filename)
{
    std::vector<std::string> datalist;
    std::ifstream inputFile;
    inputFile.open(filename.c_str());

    // Generate List from file content
    if(inputFile.is_open())
    {
        std::string line;
        while( std::getline(inputFile,line) )
        {
            datalist.push_back(line);
        }
        inputFile.close();
    }

    return datalist;
}

/**
 * Generate CSV File with same format as input file
 */
int writeOutputFile(std::string filename, std::string &reportText)
{
    std::ofstream outputFile;
    filename = "output/" + filename;    // Add output dir prefix

    // Generate CSV with same Header 
    outputFile.open(filename.c_str());
    outputFile << "DBN,School Name,Number of Test Takers,Critical Reading Mean,Mathematics Mean,Writing Mean\n";
    outputFile << reportText ;
    outputFile.close();

    return 0;
}

/**
 * Generate CSV filtered by School Name
 */
std::string searchBySchoolName(std::string &schoolName, std::vector<std::string> &datalist)
{
    std::string reportText = "";

    for(std::vector<std::string>::iterator it = std::begin(datalist); it != std::end(datalist); ++it)
    {
        std::size_t pos = it->substr(6).find(schoolName);
        if (pos != std::string::npos)
        {
            reportText = reportText + '\n' + *it;
        }
    }

    return reportText;
}

/**
 * Search Entry by DBN and return report
 */
std::string searchByDBN(std::string &dbn, std::vector<std::string> &datalist)
{
    for(std::vector<std::string>::iterator it = std::begin(datalist); it != std::end(datalist); ++it)
    {
        std::size_t pos = it->substr(0,6).find(dbn);
        if (pos != std::string::npos)
        {
            return *it;
        }
    }
    return "";
}

/**
 * Comand Line User Interface
 *  "Generate Menu and prompt inputs to the user"
 */
int cli()
{
  char option = 'q';
  do
  {
      // Print Menu 
      std::cout << "\n      Challenge C++";
      std::cout << "\n╒═══════════════════════╕";
      std::cout << "\n│ (1) Search by Name    │";
      std::cout << "\n│ (2) Search by DBN     │";
      std::cout << "\n│ (q) Exit              │";
      std::cout << "\n╘═══════════════════════╛" << std::endl;
      
      // Read User Input
      std::cout << ">> Chose Option (1,2,q): ";
      std::cin >> option;
      
      // Evaluate Option
      if(option == '1')
      {
          std::string schoolName;
          char menuFileInput = 'n';
          
          // TODO Ask School Name
          std::cout << ">> School Name: ";
          std::cin >> schoolName;

          // Prompt user for write file
          std::cout << ">> Write output to a file? (y/[n]): ";
          std::cin >> menuFileInput;

          const std::string databaseFile = "input/SAT__College_Board__2010_School_Level_Results.csv";
          std::vector<std::string> data = readDatabaseFile(databaseFile);
          if(menuFileInput == 'y')
          {
              // Prompt User for file location
              std::string outputFileName = "report.txt";
              std::cout << ">> Name of output file: ";
              std::cin >> outputFileName;

              // Print to file
              std::string reportData = searchBySchoolName(schoolName,data);
              writeOutputFile(outputFileName, reportData);

              std::cout << "Report exported to output/" << outputFileName << " file." <<std::endl;
          }
          else
          {
              // Print to cout
              std::cout << "DBN,School Name,Number of Test Takers,Critical Reading Mean,Mathematics Mean,Writing Mean";
              std::cout << searchBySchoolName(schoolName,data) << std::endl;
          }

      }
      else if (option  == '2')
      {
          // TODO Ask DBN Code
          std::string dbn;
          std::cout << ">> Type DBN Code: ";
          std::cin >> dbn;

          // Read database and Find entry by DBN
          std::cout << "DBN,School Name,Number of Test Takers,Critical Reading Mean,Mathematics Mean,Writing Mean\n";
          std::cout << searchByDBN(dbn, datalist) << std::endl;

      }
      else if (option == 'q')
      {
          return(0);
      }
      else
      {
          std::cout << "Invalid Option!" << std::endl;
      }
 
  } while(option != 'q');

  return(0);
}


int main(int argc, const char * argv[]) { 

  // Run CLI
  cli();    

  return(0);
}

