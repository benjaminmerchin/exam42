# exam42
Training for 42 exams  
Subjects can be foubd [there](https://github.com/markveligod/examrank-02-03-04-05-06)  
  
<b>(this exam is outdated) Exam Rank 02 of the common core :</b><br>There are two exercises: the first one is inter or union, the second ont is gnl or printf

<b>(this exam is outdated) Exam Rank 03 of the common core :</b><br>There are two subjects<br>They are almost the same (around 10% differences between the two subjects)<br>My personal version is relatively short and simple (130 lines)<br>To train, you have to code your own version and then compare it with [Glagan's test.sh.](https://github.com/Glagan/42-exam-rank-03)

<b>Exam Rank 04 of the common core :</b><br>There is one exercise<br>It is a very simple version of the minishell ~120 lines.<br>I took inspiration from [joann8's solution](https://github.com/joann8/ExamTraining/tree/master/exam4).<br>It should be possible to make my version even more compact (~100 lines) by replacing the type in the struct with a boolean in the case of a pipe and therefore removing the define.

<b>Exam Rank 05 of the common core :</b><br>There are three exercises<br>With my solution, you can avoid to use the .cpp and code almost everything in the .hpp, except for 2 functions, so it is way quicker.<br>You can basically copy paste most of the code most of the fime. Especially for the last exercise.<br>I used %s/textBefore/textAfter/g in vim to replace text.<br>Also don't forget the const! I counted them to make sure I had the correct number and it went smooth. Good luck :)

<b>Exam Rank 06 of the common core :</b><br>For the client, we can just use the command Netcat:
We can open 3 Terminal, in one we run the mini_serv, and in the other two we use nc to send messages between clients.
```
nc 127.0.0.1 1024     (case with server port 1024)
```
This is [nabentay's version on GitLab](https://git.nabentay.fr/nabentay/me.gi/-/blob/master/mini_serv.c)<br>
The best version that I found, basically you only need to code 50 lines since out of the 150 lines, 100 are already given in the subject.<br>
In the exam, the testing on the subject can fail randomly. On my exam, I pushed 3 times exactly the same code. I had strange errors on the last moulinette test (test9, the longest). On the second push, I had only one extra line that should not be there out of more than 13000 lines in the trace), and I validated on the 3rd try with the exact same code. Because the moulinette launch more than 2000 clients on the same server, I suspect it was one fd badly closed on the computer used for moulinette.

<!--
-->
