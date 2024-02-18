cout << "Testing Seprate Chaining :" << endl;

    pair<int, int> report_s_5000 = ReportFunction1(1, 5, 5000);
    pair<int, int> report_s_10000 = ReportFunction1(1, 5, 5000);
    pair<int, int> report_s_20000 = ReportFunction1(1, 5, 5000);

    printReport(report_s_5000, 5000);
    printReport(report_s_10000, 10000);
    printReport(report_s_20000, 20000);