source /home/manager/.pwndbg/gdbinit.py
source /home/manager/.splitmind/gdbinit.py

python
import splitmind
(splitmind.Mind()
  .right(display="stack")
  .below(display="regs")
  .below(display="backtrace", size="30%")
  .above(of="main", display="disasm")
  .show("legend", on="disasm")
).build()
end

set context-code-lines 20
set context-stack-lines 25
set show-flags on
