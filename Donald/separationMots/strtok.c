#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *str1, *str2, *tok1, *tok2, *str3, *tok3;
	char *str4, *tok4,*saveptr4;
	char *str5, *tok5,*saveptr5;
	char *str6, *tok6,*saveptr6;
	char *str7, *tok7,*saveptr7;
	char *str8, *tok8,*saveptr8;
	char *str9, *tok9,*saveptr9;
	char *str10, *tok10,*saveptr10;
	char *str11, *tok11,*saveptr11;
	char *str12, *tok12,*saveptr12;
	char *str13, *tok13,*saveptr13;

	char *saveptr1, *saveptr2, *saveptr3;
	char * pathtweet = "../Trumptweet000";
	int i,j;
	FILE * fichier1 = NULL;
	fichier1 = fopen("../mots","w+");

	char * ligne;
	size_t len = 0;
	FILE * fichier;
	fichier = fopen(pathtweet,"r+");
	while(getline(&ligne,&len,fichier)!=-1)
	{
		for (j = 1, str1 = ligne; ; j++, str1 = NULL) 
		{
			tok1 = strtok_r(str1, " ",&saveptr1);
			if (tok1 == NULL)
				break;
			for (str2 = tok1; ; str2 = NULL) 
			{
				tok2 = strtok_r(str2, "\"", &saveptr2);
				if (tok2 == NULL)
					break;
				for (str3 = tok2; ; str3 = NULL) 
				{
					tok3 = strtok_r(str3, "\n", &saveptr3);
					if (tok3 == NULL)
						break;
					for (str4 = tok3; ; str4 = NULL) 
					{
						tok4 = strtok_r(str4, ",", &saveptr4);
						if (tok4 == NULL)
							break;
						for (str5 = tok4; ; str5 = NULL)
						{
							tok5 = strtok_r(str5, "\"", &saveptr5);
							if (tok5 == NULL)
								break;
							for (str6 = tok5; ; str6 = NULL) 
							{
								tok6 = strtok_r(str6,"“", &saveptr6);
								if (tok6 == NULL)
									break;
								for (str7 = tok6; ; str7 = NULL) 
								{
									tok7 = strtok_r(str7, "\\", &saveptr7);
									if (tok7 == NULL)
										break;
									for (str8 = tok7; ; str8 = NULL) 
									{
										tok8 = strtok_r(str8, "(", &saveptr8);
										if (tok8 == NULL)
											break;			
										for (str9 = tok8; ; str9 = NULL) 
										{
											tok9 = strtok_r(str9, ")", &saveptr8);
											if (tok9 == NULL)
												break;		
											for (str10 = tok9; ; str10 = NULL) 
											{
												tok10 = strtok_r(str10, "!", &saveptr10);
												if (tok10 == NULL)
													break;

												if (tok10[0]=='@') strcpy(tok10,"@");
												if (tok10[0]=='#') strcpy(tok10,"#");
												if (tok10[0]=='w' && tok10[1]=='w' && tok10[2]=='w') strcpy(tok10,"*");
												if (tok10[0]=='h' && tok10[1]=='t' && tok10[2]=='t' && tok10[3]=='p') strcpy(tok10,"*");
												if (tok10[0]=='n' && tok10[1]=='@') strcpy(tok10,"@");
												if (tok10[0]=='n' && tok10[1]=='#') strcpy(tok10, "#");
												if (tok10[0]=='n' && tok10[1]=='h' && tok10[2]=='t' && tok10[3]=='t' && tok10[4]=='p') strcpy(tok10,"*");
												if (tok10[0]=='p' && tok10[1]=='i' && tok10[2]=='c' && tok10[3]=='.' && tok10[4]=='t') strcpy(tok10,"PIC");

												for (str11 = tok10; ; str11 = NULL) 
												{
													tok11 = strtok_r(str11, "-", &saveptr11);
													if (tok11 == NULL)
														break;
													for (str12 = tok11; ; str12 = NULL) 
													{
														tok12 = strtok_r(str12, ".", &saveptr12);
														if (tok12 == NULL)
															break;
														for (str13 = tok12; ; str13 = NULL) 
														{
															tok13 = strtok_r(str13, "/", &saveptr13);
															if (tok13 == NULL)
																break;
															printf("%s\n",tok13);
															fprintf(fichier1, "%s\n", tok13);
														}
													}
												}
											}
										}
									}
								}	
							}
						}//’ … — ' '
					}
				}
			}
		}
		fprintf(fichier1, "%s\n", "-");
	}
	fclose(fichier1);
	fclose(fichier);
	exit(EXIT_SUCCESS);
}
