#!/bin/bash
DELAY=0.01
LINE_BREAK="0a"

if [ $# -eq 1 ]; then
    DELAY=$1;
fi

column_idx=0
line_idx=0
coords_char_list=""
text=$(od -A n -t x1 -v)

for current_symbol in $text; do
    if [ "$current_symbol" == $LINE_BREAK ]; then
        line_idx=$((line_idx + 1))
        column_idx=0
    else
        column_idx=$((column_idx + 1))
        coords_char_list+="$column_idx $line_idx $current_symbol\n"
    fi
done

echo $coords_char_list

coords_char_list=$(echo -e "$coords_char_list" | shuf)

tput clear
echo "$coords_char_list" |
while read y x char; do
    if [ "$char" != "" ]; then
        tput cup $x $y
        echo -ne "\x$char"
    fi  
    sleep $DELAY;
done
tput cup $(tput lines) 0
