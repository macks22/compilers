# test0.txt

Final states: C, D, B
Expected output:
aaaaaaab   String accepted
abbbbbb    String accepted
bbb        String rejected
aaa        String accepted
           String rejected (empty string not in language)
efasd;flk  String rejected (several chars not in language)
abababa    String rejected

# test1.txt

Final states: A
Expected output:
aaaaaa        String accepted
aaa           String rejected
bbbb          String rejected
aaaaaaaaaaaa  String accepted
ccccc         String rejected

# test2.txt

Final states: A2, A3, A5
Expected output:
aaaaab      String accepted
abbbbb      String accepted
aaabbb      String rejected
b           String rejected
ab          String accepted
a           String accepted
aaaabaaaa   String rejected
abbbbaaaaa  String rejected
baaaaaa     String rejected
bbbbbbbb    String rejected
aaaaaaaa    String rejected

# test3.txt

Final states: A1abC
Expected output:
aaaaaa       String accepted
aaa          String rejected
bbbb         String rejected
aaaaaaaaaaa  String rejected
ccccc        String rejected
