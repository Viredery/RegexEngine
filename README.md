# RegexEngine
    --一个简单的正则表达式引擎
<h2>建议阅读顺序:</h2>
    RE_tree -> NFA -> DFA -> Judge
    
<h2>例子:</h2>
    Re:a(b|c)a(b|c*)
    字符串:abacccccc
    输出:ok
    
    Re:a(b|c)*
    字符串:abbcca
    输出:fail
    
<h2>主要算法</h2>
    语法分析构造正则表达式的分析树:自顶向下分析,当发生不匹配的情况时简单回溯
    正则表达式到NFA:Thompson构造法
    NFA到DFA:子集构造法
