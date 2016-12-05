=== Ringbuffer ===
2012년에 회사 다니면서 취미로 제작한, RingBuffer for Event Stream Processing 코드

초기 아이디어: Dirruptor, LMAX
기본적인 아이디어는 Disruptor과 동일한 Lock-free RingBuffer 구조이나,
다수의 이벤트 핸들러들이 병렬로 동작하는 것이 아닌, 일련의 이벤트 핸들러들이 순차적으로 적용되는 파이프라이닝 방식

 /Framework : RingBuffer Framework
 /FrameworkTest : Test using Google test framework
 /MockClientChannel : Dummy server, dummy client, simple performance test


=== Algorithm ===
2014년 NHN NEXT 알고리즘 수업 과제
CRLS (Introduction to algorithms) 3rd, Chapter 16, Activity selection problem, Knapsack problem
recursive, greedy algorithm, dynamic programming 방식 적용, 일부는 C++11의 람다 기능을 사용.

=== LookAndSay ===
Look and say algorithm (Scala)

=== ReverseWithTag ===
태그를 유지한 상태에서 문자열을 뒤집기 (Scala, Javascript)
