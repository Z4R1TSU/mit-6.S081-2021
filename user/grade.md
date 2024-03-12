# lab 6 thread

* uthread <br>
    * [x] add code to ***thread_create()*** in ***user/uthread.c***
    * [x] add code to ***thread_schedule()*** in ***user/uthread.c***
    * [x] add ***thread_switch*** in ***user/uthread_switch.S***
    * [x] ***thread_switch*** save/restore 14 callee registers (like ***swtch.S*** does) and returns to the point in the latter thread's instructions where it last left off
    * [x] modifying struct thread to hold registers
    * [x] add a call to ***thread_switch*** in ***thread_schedule***
    * [ ] pass whatever arguments you need to ***thread_switch***
    > grade:
    …d ⇡1 !2 ▓▒░░▒▓ ✔  03:42:28 PM ▓▒░
╰─ ./grade-lab-thread uthread
make: 'kernel/kernel' is up to date.
== Test uthread == uthread: OK (1.4s) 

* using threads <br>
    * [x] add lock to prevent key missing  
    ~~I am so silly that try to `./ph 2` without `make ph`~~
    * [x] how about a lock per hash bucket for speedup?
    > grade:
    …d ⇡1 !2 ▓▒░░▒▓ ✔  03:42:33 PM ▓▒░
╰─ ./grade-lab-thread ph_safe
make: 'kernel/kernel' is up to date.
== Test ph_safe == gcc -o ph -g -O2 -DSOL_THREAD -DLAB_THREAD notxv6/ph.c -pthread
ph_safe: OK (8.8s) 
… !2 ▓▒░░▒▓ ✔  8s  03:43:15 PM ▓▒░
╰─ ./grade-lab-thread ph_fast
make: 'kernel/kernel' is up to date.
== Test ph_fast == make: 'ph' is up to date.
ph_fast: OK (19.2s) 

* barrier
    * [x] You have to deal with a succession of barrier calls, each of which we'll call a round. bstate.round records the current round. You should increment bstate.round each time all threads have reached the barrier.
    * [x] You have to handle the case in which one thread races around the loop before the others have exited the barrier. In particular, you are re-using the bstate.nthread variable from one round to the next. Make sure that a thread that leaves the barrier and races around the loop doesn't increase bstate.nthread while a previous round is still using it.
    > grade:
    …d ⇡1 !2 ▓▒░░▒▓ ✔  06:16:48 PM ▓▒░
╰─ ./grade-lab-thread barrier
make: 'kernel/kernel' is up to date.
== Test barrier == gcc -o barrier -g -O2 -DSOL_THREAD -DLAB_THREAD notxv6/barrier.c -pthread
barrier: OK (4.9s) 

> lab 6 grade:

    