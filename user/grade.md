# lab 6 thread

* uthread <br>
    * [x] add code to `thread_create()` in `user/uthread.c`
    * [x] add code to `thread_schedule()` `in `user/uthread.c`
    * [x] add `thread_switch` in `user/uthread_switch.S`
    * [x] `thread_switch` save/restore 14 callee registers (like `swtch.S` does) and returns to the point in the latter thread's instructions where it last left off
    * [x] modifying struct thread to hold registers
    * [x] add a call to `thread_switch` in `thread_schedule`
    * [ ] pass whatever arguments you need to `thread_switch`