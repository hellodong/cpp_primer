## Associative Container
 ��������֧�ָ�Ч�Ĺؼ��ֲ��������.������Ҫ�Ĺ���������������**map**��**set**����׼���ṩ8����������������������ά����: 
 
 - ÿ������������һ��set, ������һ��map
 - Ҫ���ظ��ؼ��֣����������ظ��ؼ���
 - ��˳�򱣴�Ԫ�ػ��ߣ����򱣴�
 
 ����map��multimap������ͷ�ļ�map�С�����set��multiset������ͷ�ļ�set�С���������������ͷ�ļ�unordered_map��unordered_set�С�

 ### ʹ�ù�������
 ##### ʹ��map
 ���������ǵ��ʼ���:
 ```CPP
        std::istream_iterator<std::string> input(file), eof;
        std::map<std::string, size_t> word_count;

        while (input != eof)
        {
                std::cout <<" " << *input;
                word_count[*input++]++;
        }
        std::cout << "\n" << std::endl;
        for (const auto &w:word_count)
        {
                std::cout << w.first << " occurs " << w.second << " times" << std::endl;
        }
 ```
 while ѭ��ÿ�δ�����������������һ�����ʡ�ÿ�����ʶ�word_count�����±���������word��δ��map�У��±�����ᴴ��һ����Ԫ�أ��ؼ���Ϊword,ֵΪ0��
 ��ȡ���������룬for������map,��ӡÿ�����ʺͶ�Ӧ�ļ���ֵ����map����ȡһ��Ԫ�أ���õ�һ��pair���Ͷ��󡣼���˵pair��һ��ģ�����ͣ�����������Ϊfirst��second�����ݳ�Ա��map��ʹ�õ�pair��first��Ա����ؼ��֣���second�����Ӧֵ��
 ##### ʹ��set
 ```CPP
        std::map<std::string, size_t> word_count;
        std::set<std::string> exclud{"The","And", "But","Or",
                                     "the","and", "but","or"};

        while (input != eof)
        {
                std::cout <<" " << *input;
                if (exclud.find(*input) != exclud.end())
                {
                        word_count[*input]++;
                }
                input++;
        }

 ```
 �˳�����ǰ����ͬ���ڣ����Ǽ�鵥���Ƿ���ָ�������С�find()���÷���һ��������������ؼ�����set�����У�������ָ��ؼ��֣�����find����β��������
 
