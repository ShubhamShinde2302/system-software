#!/bin/bash
# Run this inside ~/Desktop/LINUX to rename your originals in place.
# It renames the .c source files and their compiled binaries.

for n in 3 4 5 6 7 8 9 10 11 12 13 14 15 16 19 20 21 22 23 24 25; do
    [ -f "ass$n.c" ] && mv -v "ass$n.c" "question_$n.c"
    [ -f "ass$n"   ] && mv -v "ass$n"   "question_$n"
done

[ -f ass17Store.c   ] && mv -v ass17Store.c   question_17_store.c
[ -f ass17Store     ] && mv -v ass17Store     question_17_store
[ -f ass17Res.c     ] && mv -v ass17Res.c     question_17_reserve.c
[ -f ass17Res       ] && mv -v ass17Res       question_17_reserve
[ -f ass18Records.c ] && mv -v ass18Records.c question_18_records.c
[ -f ass18Records   ] && mv -v ass18Records   question_18_records
[ -f ass18.c        ] && mv -v ass18.c        question_18.c
[ -f ass18          ] && mv -v ass18          question_18

echo "Done."
