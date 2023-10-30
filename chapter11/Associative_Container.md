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
 
 #### �����������
 һ��map��set�еĹؼ��ֱ�����Ψһ�ģ�����һ�������Ĺؼ��֣�ֻ��һ��Ԫ�صĹؼ��ֵ�����������multimap��multisetû�д����ƣ�����������Ԫ�ؾ�����ͬ��Ԫ�ء�
 ```cpp
 
    std::vector<int> ivec;
    for(std::vector<int>::size_type idx = 0;idx != 10;idx++ )
    {
        ivec.push_back(idx);
        ivec.push_back(idx);
    }

    std::set<int> iset(ivec.cbegin(), ivec.cend());
    std::multiset<int> multiset(ivec.cbegin(), ivec.cend());

    std::cout << "ivec size:" << ivec.size() << std::endl; // ��� 20
    std::cout << "iset size:" << iset.size() << std::endl; // ��� 10
    std::cout << "multiset size:" << multiset.size() << std::endl; // ���20
 ```
 #### �ؼ������͵�Ҫ��
 ������������ؼ�����һЩҪ�󡣶����������� --- map, multimap,set,multiset,�ؼ������ͱ��붨��Ԫ�رȽϵķ�����Ĭ������£���׼��ʹ�ùؼ������͵�<������Ƚ������ؼ��֡���set�����У��ؼ������;���Ԫ�����͡���map�����У��ؼ���������Ԫ�صĵ�һ�������͡�

 ##### ���������Ĺؼ�������
 �����ṩ�Լ�����Ĳ�������ؼ����ϵ�< ����������ṩ�Ĳ��������ڹؼ��������϶���һ��**�ϸ�����**�� ���Խ��ϸ���������С�ڵ��ڡ���������߱����»�������:
 
 - �����ؼ��ֲ�ͬͬʱ��С�ڵ��ڡ��Է������k1"С�ڵ���"k2, ��ôk2�����ܡ�С�ڵ��ڡ�k1

 ##### ʹ�ùؼ������͵ıȽϺ���
 Ϊ��ָ��ʹ���Զ���Ĳ����������ڶ��������������ʱ�ṩ���������͡��Զ���Ĳ������ͱ����ڼ������н�����Ԫ�����͸�����

 
