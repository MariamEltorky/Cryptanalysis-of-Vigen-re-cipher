#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include<math.h>
#include<map>
#include<fstream>
#include <unordered_map>
#include <algorithm>
using namespace std;
char EnglishChars[] 
={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
double Englishprobability[] = 
{0.082,0.015,0.028,0.043,0.127,0.022,0.020,0.061,0.070,0.002,0.008,0.040,0.024,0.067,0.075,0.019,0.001
,0.060,0.063,0.091,0.028,0.010,0.023,0.001,0.020,0.001};
unordered_map<string, int> umap; //to insert fitness of English Language 
// to get lines of file that contains fitness of english and insert all lines into string
vector<string> get_each_line (string line) {
vector<string> allline;
int begin = 0;
 int end = 0;
 for (int i = 0; i < line.length(); ++i) { 
 if (line[i] == '\n') {
 end = i;
 allline.push_back(line.substr(begin, end - begin));//to devide string and the delimiter is end line '\n'
 begin = (i + 1);
 }
 }
return allline;
}
//to get Quadgram keys in english from file 
string get_key (string allline) {
int i=0;
string key="";
while (allline[i] != ' ') { // to get all keys that before space
key+=allline[i];
i++;
}
if (allline[i]==' ') {
i++;
}
return key;
}
//to get Quadgram values in english from file 
string get_value(string allline) {
string value="";
int i=0;
string key="";
while (allline[i] != ' ') {
key+=allline[i];
i++;
}
if (allline[i]==' ') {
i++;
}
while (i<(allline.length())) {
value+=allline[i]; // to get all values that after space
i++;
}
return value;
}
//to convert string into integer
int convert (string st) {
 int value=0;
 stringstream convert(st); 
convert>>value;
return value;
}
//to print any vector of string
void printVector(vector<string> vect){
for (int i=0;i<vect.size();i++) {
cout<<"print Vector--> "<<vect[i]<<endl;
}
}
//----------------Finding Key Length------------------------
//to get sequences of all key lengths 2,3,4,5,.....and to the end of ciphertext
vector<string> calseqsseq (string s) {
vector<string> vect;
string st="";
int c=0;
for (int k=1;k<s.length();k++) {
c++;
for (int i=1;i<s.length();i++) {
for (int j=i;j<s.length();j=j+c) {
st+=s[j];
}
if (i<=c) { 
vect.push_back(st);
}
st="";
}
}
return vect;
}
//to Calculate occurrences of letters from substrings
vector<vector<int>> calocu (vector<string> ch) {
vector<vector<int>> twovect;
string st;
int c=0;
string acu;
vector<int> x;
int pushh=0;
for (int i=0;i<ch.size();i++) {
st+=ch[i];
for (int j=0;j<st.length();j++) {
c=1;
for (int k=0;k<st.length();k++) {
if (k!=j) { //to not compare char by itself
if (st[j]==st[k]) {
c++;
pushh=0;
for (int z=j-1;z>=0;z--) { //to compare the letter to all other letters from
 
//the left of it exist will pass because it already counted previous
if (st[j]==st[z]) {
pushh=1;
continue;
}
}
}
}
}
if (pushh==1) {
pushh=0;
}
 else{
 if (c!=0) { //if the count is not 0 and push not equal 1 that means the ocu of char must push
x.push_back(c);
}
}
}
st="";
twovect.push_back(x);
x.clear();
}
return twovect;
} 
//to Calculate The Index of Coincidence (I.C.)
double CalIC (vector<int> x,string inp) {
double sum=0;
double finalsum=0;
int temp=0;
for(int g=0;g<x.size();g++){
temp= temp+x.at(g); //to determine the length of each string to divide by it
}
for (int i=0;i<x.size();i++) {
sum=((x.at(i))*(x.at(i)-1)); //this the numerator of equation
finalsum+=sum;
}
if (temp>1) {
finalsum=finalsum/((temp)*(temp-1)); //this equation of IC 
}
return finalsum;
}
//to Calculate All The Index of Coincidence (I.C.)
vector<double> CalAllIC (double finalsum) {
vector<double> vect;
vect.push_back(finalsum); // to push all IC into vector to get Average of all after that
return vect;
}
//to Calculate The Average of Index of Coincidence (I.C.) of sequences of all key lengths
double CalAvg (vector<double> comp) {
double temp=0;
for (int i=0;i<comp.size();i++) {
temp+=comp[i];
}
return temp/comp.size();
}
//----------------Finding Key ------------------------
//get all strings according to keys length
vector<string> getStringsLength (int length,string inp) {
string shift;
vector<string> allstringsLength;
for (int j=1;j<=length;j++) { 
for (int i=j;i<inp.length();i+=length) { 
shift+= inp[i];
}
allstringsLength.push_back(shift);
shift="";
}
return allstringsLength;
}
//get all 25 substrings that shifting one from alphabet
vector<string> getSubstrings(string stringLength) {
vector<string> allsubstrings;
string st="";
int shift=0;
allsubstrings.push_back(stringLength);
for (int s=1;s<26;s++) {
st="";
for (int i=0;i<stringLength.length();i++) { //get 25 substrings shifting one of EnglishChars
for (int j=0;j<26;j++) {
if (EnglishChars[j]==stringLength[i]) {
shift=j-s;
if (shift<0) { 
st+=EnglishChars[shift+26];
}
else {
st+=EnglishChars[shift];
}
}
}
}
allsubstrings.push_back(st);
}
return allsubstrings;
 
}
//to Calculate occurrences of letters from 25 substrings that shifting one from alphabet
vector<vector<int>> calocucharstrings (vector<string> ch) {
string st;
int c=0;
string acu;
vector<vector<int>> all;
vector<int> count;
int pushh=0;
for (int i=0;i<ch.size();i++) {
for (int k=0;k<26;k++) {
c=0;
for (int j=0;j<ch[i].length();j++) {
if (EnglishChars[k]==ch[i].at(j)) { //to count the ocu of each char in 
substrings comparing to EnglishChars
c++;
}
}
count.push_back(c);
}
all.push_back(count);
c=0;
count.clear();
}
return all;
} 
//to Calculate Chi-squared Statistic to get possible keys
vector<double> getChiSquared (vector<vector<int>> all,int size) {
vector<vector<double>> allprobwithsize;
vector<double> probwithsize;
double temp=0;
for (int i=0;i<all.size();i++) {
temp=0;
for (int j=0;j<=25;j++) {
temp=size*Englishprobability[j]; //this the part of equation to calculate 
Chi-squared to get the Englishprobability
probwithsize.push_back(temp);
}
allprobwithsize.push_back(probwithsize);
}
vector<double> finalchi;
double tempchi=0;
for (int j=0;j<=25;j++) {
tempchi=0;
for (int i=0;i<=25;i++) {
tempchi+= ( pow(((all[j][i])-(allprobwithsize[j][i])),2)/(allprobwithsize[j][i]) ); //equation to calculate 
Chi-squared
}
finalchi.push_back(tempchi);
}
return finalchi;
}
//get possible keys that have minimum and second minimum Chi-squared value
vector<string> getpossiblekeys (string key1, string key2) {
vector<string> possible;
string st="";
for (int i=0;i<key1.length();i++) { //to concat key2 to letters key1
st="";
st+=key1.substr(0,i);
st+=key2.substr(i,key1.length());
possible.push_back(st);
}
for (int i=0;i<key2.length();i++) { //to concat key1 to letters key2
st="";
st+=key2.substr(0,i);
st+=key1.substr(i,key2.length());
possible.push_back(st);
}
return possible;
}
//remove duplicates from vector of possible keys 
vector<string> getuniquekeys (vector<string> possible) {
sort(possible.begin(), possible.end()); //after get all possible keys remove the strings may be duplicates
 possible.erase(unique(possible.begin(), possible.end()), possible.end());
return possible;
}
//to get plaintext of key
string get_plainText (string chiphertext,string key) {
string s="";
vector<int> plain;
 vector<int> cipher;
 vector<int> k;
 s=key;
for (int j=0;j<chiphertext.length();j++) {
for (int i=0;i<26;i++) {
if (chiphertext[j]==EnglishChars[i]) {
cipher.push_back(i);
break;
}
}
}
while (s.length()<chiphertext.length()) {
for (int i=0;i<key.length();i++) {
s+=key[i];
if (s.length()==chiphertext.length()) {
break;
}
}
}
for (int j=0;j<s.length();j++) {
for (int i=0;i<26;i++) {
if (s[j]==EnglishChars[i]) {
k.push_back(i);
break;
}
}
}
for (int i=0;i<chiphertext.length();i++) {
if ((cipher[i]-k[i]) % 26 >= 0) { 
plain.push_back((cipher[i]-k[i]));
}
 if ((cipher[i]-k[i])% 26 < 0) { 
plain.push_back((cipher[i]-k[i])+26);
}
}
string str="";
for (int j=0;j<plain.size();j++) {
for (int i=0;i<26;i++) {
if (plain[j]==i) {
str+=EnglishChars[i];
}
}
}
return str;
} 
//-------------------Fitness Of English----------------------
//get Quadgram letters from each plain text
vector<string> get_four_letter (string plaintext) {
vector<string> foursubstrings;
string st="";
for (int i=0;i<=plaintext.length();i++) {
st="";
if (i+3<plaintext.length()){
st=plaintext.substr(i,4);
foursubstrings.push_back(st);
}
}
return foursubstrings;
}
//get Calculate QuadGram of each all plaintext
double get_QuadGrams (vector<string> foursubstrings) {
double TotalQuad=0;
for (int i=0;i<foursubstrings.size();i++) {
TotalQuad+=log10((double)umap[foursubstrings[i]]); //equation to calculate 
QuadGram
}
return TotalQuad;
}
void main () {
 string to_decrypt="";
 cout<<"Enter The CipherText You Want To Decrypt With Capital Letters Only :"<<endl;
 cin>>to_decrypt;
 if (to_decrypt.length()<100) {
 cout<<"This CipherText Is Short. please, Enter Bigger one :"<<endl;
 cin>>to_decrypt;
 }
 if (to_decrypt.length()>100) {
 cout<<"-------------Please Wait-------------------"<<endl;
 string inp=" "+to_decrypt;
 vector<int> minvector;
vector<int> secondminvector;
vector<string> plaintexts;
vector<string> uniquekey;
 int maxmax=0; //number of all substrings to calculate all Ic for them
 for (int i=inp.length()-1;i>0;i--) {
 maxmax=maxmax+i;
 }
vector<string> vect;
vect=calseqsseq(inp);
vector<vector<int>> vect2;
vect2=calocu(vect);
vector<double> allIc;
for (int i=0;i<maxmax;i++) {
double x=CalIC(vect2[i],inp);
allIc.push_back(x);
}
vector<double> AVG;
vector<double> tempIc;
int sum=0;
for (int i=1;i<inp.length();i++) {
sum=0;
tempIc.clear();
for (int x=i;x>0;x--) {
sum=sum+x;
}
for (int j=sum-1;j>(sum-i)-1;j--) {
tempIc.push_back(allIc[j]);
}
AVG.push_back(CalAvg(tempIc));
}
double max=AVG[0];
int lenkey;
for (int i=0;i<10;i++) {
if (AVG[i]>max) {
max=AVG[i];
lenkey=i+1;
}
}
vector<string> allstringskeylength;
allstringskeylength=getStringsLength(lenkey,inp); //get all strings of the correct length
for (int r=0;r<allstringskeylength.size();r++) {
vector<vector<int>> ocustrings;
ocustrings=calocucharstrings(getSubstrings(allstringskeylength[r]));
vector<double> chisquared;
chisquared=getChiSquared(ocustrings,allstringskeylength[r].length());
double min=chisquared[0]; //to get possible keys minimum and second minimum
double secondmin=chisquared[1];
int flag=0;
int flagsecond=0;
if (secondmin<min) {
double temp=min;
min=secondmin;
secondmin=temp;
}
for (int i=1;i<26;i++) {
if (chisquared[i]<min) {
secondmin=min;
min=chisquared[i];
flag=i;
}
else if (chisquared[i]<secondmin ) {
secondmin=chisquared[i];
flagsecond=i;
}
}
minvector.push_back(flag);
if (secondmin-min <= 20){ //range to get second minimum
secondminvector.push_back(flagsecond);
}
else if (secondmin-min > 20){
secondminvector.push_back(flag);
}
}
vector<char> finalkey;
string keyy="";
string keyy2="";
for (int i=0;i<minvector.size();i++) {
keyy+=(EnglishChars[minvector[i]]); //get chars of the first key
}
for (int i=0;i<secondminvector.size();i++) {
keyy2+=(EnglishChars[secondminvector[i]]); //get chars of the second key
}
if (keyy!=keyy2) { // if first key not equal second will calculate the fitness
 //of each plaintext and get the correct key and plaintext
ifstream f;
 f.open("file.txt"); //open file that contains English Quadgrams to test the fitness of 
plaintext according to English
string st="";
 getline(f,st,'$');
string key="";
int value=0;
vector<string> lines=get_each_line(st); 
for (int z=0;z<lines.size();z++) {
string key=get_key (lines[z]);
string stringvalue=get_value(lines[z]);
value=convert(stringvalue);
umap.insert(make_pair(key,value)); //to insert all file into unordered_map
}
vector<string> possiblekey;
possiblekey=getpossiblekeys(keyy,keyy2);
uniquekey=getuniquekeys(possiblekey);
/*cout<<"------The Possible Keys--------"<<endl;
printVector(uniquekey);*/
for (int i=0;i<uniquekey.size();i++) {
plaintexts.push_back(get_plainText(to_decrypt,uniquekey[i]));
}
vector<string> foursubstrings;
vector<double> FinalQuad;
for (int z=0;z<plaintexts.size();z++) {
foursubstrings.clear();
foursubstrings=get_four_letter(plaintexts[z]);
FinalQuad.push_back(get_QuadGrams(foursubstrings));
}
double bestfitness=0;
double maxbest=FinalQuad[0];
int bestind=0;
for (int i=0;i<FinalQuad.size();i++) {
if (FinalQuad[i]>max) {
max=FinalQuad[i];
bestind=i;
}
}
cout<<"----------------KEY AND PLAIN TEXT--------------------"<<endl;
//to print key and plaintext that have the higher Quadgram means it is more likely to be English 
cout<<"Key---> "<<uniquekey[bestind]<<endl;
cout<<"PlainText---> "<<plaintexts[bestind]<<endl;
 
}
else{ //if first key equal second that will get key and plaintext immediately
cout<<"----------------KEY AND PLAIN TEXT--------------------"<<endl;
cout<<"Key---> "<<keyy<<endl;
cout<<"PlainText---> "<<get_plainText(to_decrypt,keyy)<<endl;
}
}
system("pause");
}
