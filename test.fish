#! /bin/fish

function report
  set_color blue
  echo -e $argv[2]
  set_color normal
  fish -c "$argv[1]"
  echo
end

report "./target/main > /dev/stdout" "redirect to stdout"
report "./target//main > /dev/stderr" "redirect to stderr"

report "./target//main > ./target//test-output-file" "redirect to regular file"

report "./target//main > /dev/pts/4" "redirect to pseudo terminal /dev/pts/4"

report "./target//pseudo-terminal" "creating pseudo terminal\nuse `screen <device pts>` to connect to the slave and test it"
