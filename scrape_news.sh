#!/bin/bash
text=$(wget -q -O - https://www.ynetnews.com/category/3082 | sed 's/"/\
	/g' |  grep https://www.ynetnews.com/article/[a-zA-Z0-9]* | sort | uniq)

#sed 's/#autoplay/ /g' 					
text="${text//"#autoplay"/''}"

gantz="Gantz"
netanyahu="Netanyahu"
websiteUrl="https://www.ynetnews.com/article/"
numOfArticles=$(grep -o $websiteUrl <<< $text | wc -l )

#echo "the number of articles is:" ${numOfArticles}
#echo -e "full text" ${text}

for((i=1;i<=numOfArticles;i++)); do
#	echo "Running Line is " $i "out of" $numOfArticles

	#get the full link 	
	link=$(echo $text | cut -d ' ' -f $i )

#	echo "site is" $link

	articleData=$(wget -q -O - $link)

	#echo $articleData
 	
	netanyahuCount=$(grep $netanyahu <<< $articleData -o | wc -l)
	gantzCount=$(grep $gantz <<<  $articleData -o | wc -l)

#	echo "netanyahu count is : " $netanyahuCount 
#	echo "gantz count is :     " $gantzCount

	if [ $netanyahuCount -eq 0 ] && [ $gantzCount -eq 0 ]; then
		string_to_add=", -"
	else
		string_to_add=", ${netanyahu}, ${netanyahuCount}, ${gantz}, ${gantzCount}"
	fi

	echo $link$string_to_add

#	echo "string to add is" $string_to_add

	newString=$link$string_to_add
#	echo "NEWSTRING:" $newString

#	text="${text//$link/$newString}"

#	newer_text=$(tr ' ' '\n' <<< $new_text)
done

#sed 's/ /\n/g' <<< $text 

#echo $text
#echo "\n"
#echo "\n"
#echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2"
#echo -e $text


