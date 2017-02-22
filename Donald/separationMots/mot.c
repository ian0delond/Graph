	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>



int main(int argc, char const *argv[])
	{
		int test=0;
		char lecture;

		FILE * fichier = NULL;
		FILE * fichier1 = NULL;
		FILE * fichier2 = NULL;
		FILE * fichier3 = NULL;
		FILE * fichier4 = NULL;
		FILE * fichier5 = NULL;
		fichier = fopen("../Trumptweet","r+");
		fichier1 = fopen("../mots","w+");
		fichier2 = fopen("../mentions","w+");
		fichier3 = fopen("../link","w+");
		fichier4 = fopen("../hashtag", "w+");
		fichier5 = fopen("../picture","w+");
		while(1)
		{
			lecture = fgetc(fichier);
			if(lecture==EOF)
			{
				break;
			}
			//printf("Lecture = %c\n",lecture);
			while((lecture<='Z'&&lecture>='A')||(lecture<='z'&&lecture>='a')||lecture=='\'')
			{
				if(lecture=='h')
				{
					lecture = fgetc(fichier);
					if(lecture=='t')
					{
						lecture = fgetc(fichier);
						if(lecture=='t')
						{
							lecture=fgetc(fichier);
							if(lecture=='p')
							{
								lecture=fgetc(fichier);
								fprintf(fichier3,"http");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier3,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier3, "\n");
							}else{
								fprintf(fichier1,"htt");
							}
						}
						else
						{
							fprintf(fichier1,"ht");
						}
					}
					else
					{
						fprintf(fichier1,"h");
					}

				}
				if(lecture=='p')
				{
					lecture = fgetc(fichier);
					if(lecture=='i')
					{
						lecture = fgetc(fichier);
						if(lecture=='c')
						{
							lecture=fgetc(fichier);
							if(lecture=='.')
							{
								lecture=fgetc(fichier);
								fprintf(fichier5,"pic.");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier5,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier5, "\n");
							}else{
								fprintf(fichier1,"pic");
							}
						}
						else
						{
							fprintf(fichier1,"pi");
						}
					}
					else
					{
						fprintf(fichier1,"p");
					}

				}
				fprintf(fichier1,"%c",lecture);
				lecture = fgetc(fichier);
				test=1;
			}
			if(lecture=='@')
			{
				while((lecture<='Z'&&lecture>='A')||(lecture<='z'&&lecture>='a')||lecture=='_'||lecture=='@'||(lecture>='0'&&lecture<='9'))
				{
				if(lecture=='h')
				{
					lecture = fgetc(fichier);
					if(lecture=='t')
					{
						lecture = fgetc(fichier);
						if(lecture=='t')
						{
							lecture=fgetc(fichier);
							if(lecture=='p')
							{
								lecture=fgetc(fichier);
								fprintf(fichier3,"http");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier3,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier3, "\n");
							}else{
								fprintf(fichier1,"htt");
							}
						}
						else
						{
							fprintf(fichier1,"ht");
						}
					}
					else
					{
						fprintf(fichier1,"h");
					}

				}
				if(lecture=='p')
				{
					lecture = fgetc(fichier);
					if(lecture=='i')
					{
						lecture = fgetc(fichier);
						if(lecture=='c')
						{
							lecture=fgetc(fichier);
							if(lecture=='.')
							{
								lecture=fgetc(fichier);
								fprintf(fichier5,"pic.");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier5,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier5, "\n");
							}else{
								fprintf(fichier1,"pic");
							}
						}
						else
						{
							fprintf(fichier1,"pi");
						}
					}
					else
					{
						fprintf(fichier1,"p");
					}

				}

					fprintf(fichier2,"%c",lecture);
					lecture = fgetc(fichier);
				}
				fprintf(fichier2,"\n");
			}
			if(lecture=='#')
			{
				fprintf(fichier4,"#");
				lecture=fgetc(fichier);
				while((lecture<='Z'&&lecture>='A')||(lecture<='z'&&lecture>='a')||lecture=='_'||(lecture>='0'&&lecture<='9'))
				{
				if(lecture=='h')
				{
					lecture = fgetc(fichier);
					if(lecture=='t')
					{
						lecture = fgetc(fichier);
						if(lecture=='t')
						{
							lecture=fgetc(fichier);
							if(lecture=='p')
							{
								lecture=fgetc(fichier);
								fprintf(fichier3,"http");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier3,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier3, "\n");
							}else{
								fprintf(fichier1,"htt");
							}
						}
						else
						{
							fprintf(fichier1,"ht");
						}
					}
					else
					{
						fprintf(fichier1,"h");
					}

				}
				if(lecture=='p')
				{
					lecture = fgetc(fichier);
					if(lecture=='i')
					{
						lecture = fgetc(fichier);
						if(lecture=='c')
						{
							lecture=fgetc(fichier);
							if(lecture=='.')
							{
								lecture=fgetc(fichier);
								fprintf(fichier5,"pic.");
								while(lecture!=' '&&lecture!='"'&&lecture!='\f')
								{
									fprintf(fichier5,"%c",lecture);
									lecture=fgetc(fichier);
								}
								fprintf(fichier5, "\n");
							}else{
								fprintf(fichier1,"pic");
							}
						}
						else
						{
							fprintf(fichier1,"pi");
						}
					}
					else
					{
						fprintf(fichier1,"p");
					}

				}
					fprintf(fichier4,"%c",lecture);
					lecture = fgetc(fichier);
				}
				fprintf(fichier4,"\n");
			}

			if(test==1)
			{
				fprintf(fichier1,"\n");
				test=0;
			}

		}

		fclose(fichier);
		fclose(fichier1);
		fclose(fichier2);
		fclose(fichier3);
		fclose(fichier4);
		fclose(fichier5);
		return 0;
	}