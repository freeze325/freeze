/* ����jsoncpp��ʹ��
 * dxh1688@gmail.com
 */

#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace std;
using namespace Json;    //json�������ռ�

int main()
{
    /*JSON DATA as following:            //һ��json���͵�����    
    {
        "test : 5
    }*/

    string test = "{\"test\" : 5}";        //�������ĵ�json���͵�����
                  
    //�����漰json�Ĳ��������ں������漰���˴�Ϊ��Ӧ�ã������ͣ��㶮��
    Reader reader;
    Value value;

    if (reader.parse(test, value))
    {
        int i = 0;

        if (!value["test"].isNull())
        {
            i = value["test"].asInt();
            cout << i << endl;
        }
    }

    Json::StyledWriter writer;   
    std::string output = writer.write(value);   
    std::cout<<output;   

    std::ofstream file("test.json" );   
    file<<output;  
    file.flush();

    return 0;
}