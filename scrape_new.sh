#!/bin/bash

wget -O - https://www.ynetnews.com/category/3082 | sed 's/"/\
        /g' |  grep https://www.ynetnews.com/article/[a-zA-Z0-9]* | sort | uniq

