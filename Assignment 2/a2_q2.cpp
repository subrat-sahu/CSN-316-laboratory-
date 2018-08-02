#include <bits/stdc++.h>
using namespace std;

int dec(string a, int s, int e)
{
    int x = 0;

    for (int i = s - 1; i < e; i++)
    {
        if (a[i] >= '0' && a[i] <= '9')
        {
            int y = int(a[i] - '0');
            y = y * pow(16, 3 - i);
            x += y;
        }
        else if (a[i] >= 'a' && a[i] <= 'f')
        {
            int y = (int)(a[i] - 'a' + 10);
            y = y * pow(16, 3 - i);
            x += y;
        }
    }
    return x;
}

int calc_checksum(vector<string> s)
{
    int x = 0;

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
            continue;

        int y = dec(s[i], 1, 4);
        x += y;
        cout << x << endl;
        if (x > 65535)
        {
            x = x - 65536;
            x += 1;
            cout << x << endl;
        }
    }

    return x;
}

int main()
{

    vector<string> s;
    for (int i = 0; i < 10; i++)
    {
        string x;
        cin >> x;
        s.push_back(x);
    }

    cout << endl;
    cout << "Details of IP Packet received :" << endl;

    cout << "Type: " << dec(s[0], 1, 1) << endl;
    cout << "Header Length: " << dec(s[0], 2, 2) << endl;
    cout << "Service Type: " << dec(s[0], 3, 4) << endl;
    cout << "Total length: " << dec(s[1], 1, 4) << endl;
    cout << "Identification field: " << dec(s[2], 1, 4) << endl;
    cout << "Flag and Fragment Offset: " << s[3] << endl;
    cout << "TTL: " << dec(s[4], 1, 2) << endl;
    cout << "Protocol: " << dec(s[4], 3, 4) << endl;
    cout << "Checksum received: " << dec(s[5], 1, 4) << endl;
    cout << "Source IP address: " << s[6] + s[7] << endl;
    cout << "Destination IP address: " << s[8] + s[9] << endl;

    int a;
    a = calc_checksum(s);

    a = pow(2, 16) - a - 1;

    stringstream stream;
    stream << hex << a;
    string result(stream.str());

    cout << "Calculated Checksum: " << result << endl;
    cout << "Given Checksum: " << s[5] << endl;
    if (a == dec(s[5], 1, 4))
        cout << "Correct IP header" << endl;
    else
        cout << "Incorrect IP header" << endl;
    return 0;
}

