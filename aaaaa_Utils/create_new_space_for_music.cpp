#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

// Compiled with:
// g++ -std=c++20 -pedantic -Wall -Wextra -Werror -Wshadow -Wsign-conversion -g new_song_folder.cpp  -o create_new_song
using std::cout;
using std::string;


// create_new_song <BAND/ARTIST NAME> <SONG_NAME> <>

// [0x1, 0x2, 0x3, ...]



int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cerr << "Cannot run without <BAND/ARTIST NAME> <SONG_NAME> arguments. Terminating..." << "\n";
        return 1;
    }

    const string main_catalog_name { "Transcriptions" };
    const fs::path program_path { fs::current_path() };
    fs::path transcriptions_path { program_path.parent_path()};

    if (transcriptions_path.filename() != main_catalog_name) {
        std::cerr << "The program must be in the utils folder (aaaaa_Utils) while being run..." 
        << "\n";
        return 1;
    }

    const string BAND_NAME { argv[1] };
    const string SONG_NAME { argv[2] };


    cout << "Program ran with the following arguments" << "\n";
    for (int i = 0; i < argc; ++i) {
        cout << "Argument " << i << ": " << argv[i] << "\n"; 
    }
    cout << "Checking if a band's folder already exists..." << "\n";

    const fs::path maybe_band_directory { transcriptions_path.concat("/" + BAND_NAME) };

    cout <<  maybe_band_directory << "\n";

    if (fs::exists(maybe_band_directory)) {
        cout << "Band already exists!" << "\n";
    }
    else {
        cout << "Band is new. Creating a new folder for the band..." << "\n";
        if (fs::create_directory(maybe_band_directory)) {
            cout << "Successfully created a new folder for the new band: " << BAND_NAME << "\n";
        }
        else {
            std::cerr << "Directory could not be created. Terminating...\n";
            return 1;
        }
    }


    // Create a new folder for the new song (if it does not already exist??)
    fs::path maybe_new_song_dir { maybe_band_directory};
    maybe_new_song_dir += "/" + SONG_NAME;

    if (fs::exists(maybe_new_song_dir)) {
        cout << "Song already exists!" << "\n";
    }
    else {
        cout << "Song is new. Creating a new folder for the song..." << "\n";
        if (fs::create_directory(maybe_new_song_dir)) {
            cout << "Successfully created a new folder for the new song: " << SONG_NAME << "\n";
        }
        else {
            std::cerr << "Directory could not be created. Terminating...\n";
            return 1;
        }
    }


    fs::path new_song_structure_p { maybe_new_song_dir};
    new_song_structure_p += "/";
    new_song_structure_p += "structure_" + BAND_NAME + "_" + SONG_NAME + ".txt";

    {
    std::ofstream ofs(new_song_structure_p);
    ofs << "Hello Song! :)"; 
    }

    // ./create_new_song 2_Moja_Kapela Buka

    cout << "Program finished\n" << "\n";
    return 0;

}