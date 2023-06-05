void test2Csv(string dir, TestRes results, int num){
    std::ofstream file;
    file.open(dir);

    double *arrs[8] = {results.uniformAvg, results.uniformDev,
                        results.skew1Avg, results.skew1Dev,
                        results.skew2Avg, results.skew2Dev,
                        results.skew3Avg, results.skew3Dev} ;

    string inLine;
    inLine += "uniformAvg,uniformDev,skew1Avg,skew1Dev,skew2Avg,skew2Dev,skew3Avg,skew3Dev\n";
    file << inLine;
    for (int i = 0; i<num; i++){
        inLine = "";
        for (int j = 0; j<8; j++){
            inLine += to_string(arrs[j][i]) + (j<7 ? "," : "");
        }
        inLine += "\n";
        file << inLine;
    }
    
}