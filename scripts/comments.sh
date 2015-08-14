#!/bin/bash

for file in $1/*.cc; do
    echo "$file"
    perl -e 'my $in_comment = 0; while (<>) { $in_comment = 1 if m{\Q/*\E}; print if $in_comment; $in_comment = 0 if m{\Q*/\E}; }' $file
done;
