#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <cctype>
namespace fs = std::filesystem;

// Compiled with:
// g++ -std=c++20 -pedantic -Wall -Wextra -Werror -Wshadow -Wsign-conversion -g create_new_space_for_music.cpp  -o create_new_space_for_music
using std::cout;
using std::string;


// create_new_song <BAND/ARTIST NAME> <SONG_NAME> <>

// [0x1, 0x2, 0x3, ...]

enum class music_param {
    band,
    song
};


string parse_music_param(music_param mp) {

    switch (mp) {
        case music_param::band:
            return "band";
        case music_param::song:
            return "song";
        default:
            throw std::invalid_argument("FATAL: Cotrol reached enum value not declared for parse: other that music_param::band and music_param::song");
    }

}

int create_new_space_for_music(music_param mp, const string& name_song_or_band, const fs::path& p) {

    const string music_param_name { parse_music_param(mp) };
    string first_letter_upper_music_param_name { music_param_name };
    first_letter_upper_music_param_name[0] = std::toupper(first_letter_upper_music_param_name[0]);

    if (fs::exists(p)) {
        cout << first_letter_upper_music_param_name << " already exists!" << "\n";
        return 0;
    }
    else {
        cout << first_letter_upper_music_param_name << " is new. Creating a new folder for the song..." << "\n";
        if (fs::create_directory(p)) {
            cout << "Successfully created a new folder for the new " << music_param_name << ": "  <<  name_song_or_band << "\n";
            return 0;
        }
        else {
            throw "Directory could not be created. Terminating...\n";
            return 44;
        }
    }
}


// create_new_space_for_music(band/song, band_name/song_name, )


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


    create_new_space_for_music(music_param::band, BAND_NAME, maybe_band_directory);


    // Create a new folder for the new song (if it does not already exist??)
    fs::path maybe_new_song_dir { maybe_band_directory};
    maybe_new_song_dir += "/" + SONG_NAME;


    create_new_space_for_music(music_param::song, SONG_NAME, maybe_new_song_dir);


    fs::path new_song_structure_p { maybe_new_song_dir};
    new_song_structure_p += "/";
    new_song_structure_p += "structure_" + BAND_NAME + "_" + SONG_NAME + ".txt";

    {
    std::ofstream ofs(new_song_structure_p);
    ofs << "Hello Song! :)"; 
    }

    // ./create_new_space_for_music 2_Moja_Kapela Buka

    cout << "Program finished\n" << "\n";
    return 0;

}