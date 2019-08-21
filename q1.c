#include<stdio.h> 
#include<string.h> 

char findClass(char str[])  {
	int ip=0;
	for(int i=0; i<12; i++)
		if(str[i]=='.')
			break;
		else
			ip=(ip*10)+str[i]-'0';
	if (ip >=1 && ip <= 126) 
		return 'A'; 
	else if (ip >= 128 && ip <= 191) 
		return 'B'; 
	else if (ip >= 192 && ip <= 223) 
		return 'C'; 
	else if (ip >= 224 && ip <= 239) 
		return 'D'; 
	else
		return 'E'; 
}

void separate(char str[], char ipClass) {
	char network[12], host[12]; 
	for (int k = 0; k < 12; k++) 
		network[k] = host[k] = '\0'; 
	int num=0,i=0,j=0;
	if (ipClass >= 'A' && ipClass <= 'C') {
		num=ipClass-'A'+1;
		while (num > 0) { 
			network[i++] = str[j++]; 
			if (str[j] == '.') 
				num--; 
		}
		j++;
		i=0;
		while(str[j]!='\0')
			host[i++]=str[j++];
		printf("Network ID is %s\n", network); 
		printf("Host ID is %s\n", host); 
	}
	else
		printf("IP address is not divided into Network and Host ID in this class.\n"); 
}
int main() {
	char str[50];
	scanf("%s",&str); 
	char ipClass = findClass(str); 
	printf("Given IP address belongs to Class %c\n", ipClass); 
	separate(str, ipClass); 
	return 0; 
} 
