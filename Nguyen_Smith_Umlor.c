#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encrypt_decrypt(char ch, int k[]);

int main(int argc, char* argv[]){
	int key[26];
	char keyletter[strlen(argv[2])];
	int decryptedkey[26];
	int count = 25;
	char ch;
	FILE *fin, *fout;
	
	//Error checking for command line arguments is five
	if(argc != 5){
		printf("Usage: cipher inputFile key outputFile option(e or d)\n");
		printf("Option e for encryption and d for decryption");
		exit(1);
	}
	
	//array of the whole alphabet
	char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	
	//copy the key into the keyletter
	strcpy(keyletter,argv[2]);
	
	//create the key
	for(int i = 0; i < 26; i++){
		if(i < strlen(keyletter)){
			if(isupper(keyletter[i])){
				key[i] = keyletter[i] - 'A';
			}
			if(islower(keyletter[i])){
				key[i] = keyletter[i] - 'a';
			}
			exit(1);
		}
		else{
			int j = 0;
			while(j < strlen(keyletter)){
				if(count == key[j]){
					count--;
					j = 0;
				}
				else{
					j++;
				}
			}
			key[i] = count;
			count--;
		}
	}
	
	//open the files
	fin = fopen(argv[1], "r");
	fout = fopen(argv[3], "w");
	

	//decrypt
	if(strcmp(argv[4], "d") == 0){
		for(int i = 0; i < 26; i++){
			decryptedkey[key[i]] = i;
		}
		for(int i = 0; i < 26; i++){
			key[i] = decryptedkey[i];
		}
	}
	
	//error handling for the file to open
	if(fin == NULL || fout == NULL){
		printf("File could not be opened\n");
	}
	
	//loop to encrypt or decrypt
	while(fscanf(fin, "%c", &ch) != EOF){
		fprintf(fout,"%c", encrypt_decrypt(ch, key));
	}

	fclose(fin);
	fclose(fout);

	return 0;
}

char encrypt_decrypt(char ch, int k[]){
	int index;

	if(isupper(ch)){
		index = ch - 'A';
		ch = k[index] + 'A';
		return ch;
	}

	if(islower(ch)){
		index = ch - 'a';
		ch = k[index] + 'a';
		return ch;
	}

	return ch;
}
