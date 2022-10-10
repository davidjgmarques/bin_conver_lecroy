
vector <string> trim_name( string full_name, char delimiter) {

    string trimmed_name;
    vector <string> tokens;
    stringstream check1(full_name);
    string intermediate;
    while(getline(check1, intermediate, delimiter)) tokens.push_back(intermediate);

    return tokens;
}

void read_file_time_vs_amplitude (string file, vector<double>& time, vector<double>& amplitude){

    string line, extension;
    ifstream myfile;
    double t, ampl;

    myfile.open(file.c_str());
    vector <string> name_trim = trim_name(file, '/');
    cout << "\nFile opened: " << name_trim.back() << endl;

    cout << "Adding file name to list..." << endl;

    if ( trim_name(name_trim.back(),'.')[1].compare("txt") == 0) {
        cout << "This file is a text file (.txt)" << endl;
        extension = "txt";
    }
    else if ( trim_name(name_trim.back(),'.')[1].compare("trc") == 0) {
        cout << "This file is a Lecroy binary file (.trc)" << endl;
        extension = "trc";
    }

    cout << "Writing file to vector..." << endl;

    if ( extension.compare("txt") == 0 ) {

        for ( int j = 0; j < 5; j++)  getline( myfile, line );  //ignore first 5 lines 
        while ( getline ( myfile, line ) ) {

            istringstream iss ( line );	//creates string consisting of a line
            string token;

            getline (iss, token, '\t');
            t = (double) stod(token);
            time.push_back(t);
            //cout << "t: " << t << endl;

            getline (iss, token, '\t');
            ampl = (double) stod(token);
            amplitude.push_back(ampl);
            //cout << "ampl: " << ampl << endl;
        }
    }  

    else if ( extension.compare("trc") == 0 ) {   
        
        lecroyparser::lecroy_wavedesc_2_3 header;
        int16_t* waveform = nullptr;
        bool res = lecroyparser::read(file, header, waveform);

        double x_offset = header.horiz_offset;
        double x_interval = header.horiz_interval;
        double y_gain = header.vertical_gain;
        double y_offset = header.vertical_offset;

        for ( long int i = 0; i < header.wave_array_count; ++i) {
            
            time.push_back(x_offset + x_interval * i );
            amplitude.push_back( waveform[i] * y_gain - y_offset);
        }

        delete[] waveform;
    }

    myfile.close();
}