## Scheduler

* Quick overview of goals of scheduler
  * Don't starve anyone
  * Fast response
  * Fast completion time

## Shell

* Overview

  * Parent
    1. Print a prompt
    2. Parse command line
    3. Fork child
    4. Wait for child
    5. Goto 1
  * Child
    1. Exec process
    2. If exec failed, exit

* Demo
  * `strtok()`
  * Pointers review
  * How to load up argv for exec