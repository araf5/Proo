#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void display_highscore();
void reset_highscore();
void show_help();
void update_highscore(float, char[]);

int main() {
    int correct, i;
    float score;
    char option;
    char username[20];

    while (1) {
        system("cls");
        printf("\t\t\tC PROGRAM QUIZ GAME\n");
        printf("\n\t\t----------------------------------------");
        printf("\n\t\t   WELCOME TO THE QUIZ GAME ");
        printf("\n\t\t----------------------------------------");
        printf("\n\t\t > Press S to start the game");
        printf("\n\t\t > Press V to view the highest score");
        printf("\n\t\t > Press R to reset score");
        printf("\n\t\t > Press H for help");
        printf("\n\t\t > Press Q to quit");
        printf("\n\t\t----------------------------------------\n\n");

        option = toupper(getch());

        switch (option) {
            case 'V':
                display_highscore();
                break;
            case 'H':
                show_help();
                getch();
                break;
            case 'R':
                reset_highscore();
                getch();
                break;
            case 'Q':
                exit(0);
            case 'S':
                system("cls");
                printf("\nEnter your name: ");
                gets(username);

                system("cls");
                printf("\n Welcome %s to the Quiz Game", username);
                printf("\n You will be asked 3 questions in the Warmup Round.");
                printf("\n You need 2 correct answers to proceed to the Challenge Round.");
                printf("\n Good luck!\n\n Press any key to continue.");
                getch();

                correct = 0;

                // Warmup round
                for (i = 1; i <= 3; i++) {
                    system("cls");

                    if (i == 1) {
                        printf("\nQ1. What is the largest planet in the solar system?");
                        printf("\nA. Jupiter  B. Earth\nC. Mars  D. Saturn");
                        if (toupper(getch()) == 'A') correct++;
                    } else if (i == 2) {
                        printf("\nQ2. Who is known as the father of computers?");
                        printf("\nA. Alan Turing  B. Charles Babbage\nC. Steve Jobs  D. Bill Gates");
                        if (toupper(getch()) == 'B') correct++;
                    } else if (i == 3) {
                        printf("\nQ3. What is the chemical symbol for water?");
                        printf("\nA. H2O  B. CO2\nC. O2  D. NaCl");
                        if (toupper(getch()) == 'A') correct++;
                    }
                }

                if (correct >= 2) {
                    goto challenge_round;
                } else {
                    printf("\nSorry, you are not eligible for the Challenge Round.\n");
                    getch();
                    break;
                }

challenge_round:
                system("cls");
                printf("\n\nCongratulations %s! Welcome to the Challenge Round.", username);
                printf("\nYou will be asked 5 questions. Each correct answer is worth $100,000.\n");
                correct = 0;

                // Challenge round
                for (i = 1; i <= 5; i++) {
                    system("cls");

                    if (i == 1) {
                        printf("\nQ1. Who developed the theory of relativity?");
                        printf("\nA. Newton  B. Einstein\nC. Galileo  D. Bohr");
                        if (toupper(getch()) == 'B') correct++;
                    } else if (i == 2) {
                        printf("\nQ2. Which is the smallest continent?");
                        printf("\nA. Asia  B. Australia\nC. Europe  D. Antarctica");
                        if (toupper(getch()) == 'B') correct++;
                    } else if (i == 3) {
                        printf("\nQ3. What is the capital of Canada?");
                        printf("\nA. Toronto  B. Ottawa\nC. Vancouver  D. Montreal");
                        if (toupper(getch()) == 'B') correct++;
                    } else if (i == 4) {
                        printf("\nQ4. Which element is needed for combustion?");
                        printf("\nA. Oxygen  B. Nitrogen\nC. Carbon  D. Helium");
                        if (toupper(getch()) == 'A') correct++;
                    } else if (i == 5) {
                        printf("\nQ5. What is the fastest land animal?");
                        printf("\nA. Cheetah  B. Lion\nC. Horse  D. Leopard");
                        if (toupper(getch()) == 'A') correct++;
                    }
                }

                score = (float)correct * 100000;
                system("cls");

                if (score > 0.00 && score < 500000) {
                    printf("\nCongratulations! You won $%.2f", score);
                    goto final;
                } else if (score == 500000) {
                    printf("\nYou won the maximum prize of $500,000! Congratulations!");
                } else {
                    printf("\nSorry, you didn't win any cash. Better luck next time!");
                }

final:
                printf("\n\nPress Y to play again, or any other key to return to the main menu.");
                if (toupper(getch()) == 'Y') {
                    goto challenge_round;
                } else {
                    update_highscore(score, username);
                }
                break;
        }
    }

    return 0;
}

void display_highscore() {
    system("cls");
    char name[20];
    float score;
    FILE *f = fopen("highscore.txt", "r");

    if (f == NULL) {
        printf("\nNo highscore available.\n");
    } else {
        fscanf(f, "%s%f", name, &score);
        printf("\n%s holds the highest score of $%.2f\n", name, score);
        fclose(f);
    }
    getch();
}

void reset_highscore() {
    system("cls");
    FILE *f = fopen("highscore.txt", "w");
    fprintf(f, "%s\n%.2f", "None", 0.00);
    fclose(f);
    printf("\nHighscore reset.\n");
}

void show_help() {
    system("cls");
    printf("\nWelcome to the Random Quiz Game!");
    printf("\n1. There are two rounds: Warmup and Challenge.");
    printf("\n2. Answer at least 2 out of 3 questions correctly in the Warmup to proceed.");
    printf("\n3. In the Challenge Round, answer 5 questions to win up to $500,000.");
    printf("\nGood luck and have fun!\n");
}

void update_highscore(float score, char player[20]) {
    system("cls");
    char name[20];
    float highscore;
    FILE *f = fopen("highscore.txt", "r");

    if (f == NULL) {
        f = fopen("highscore.txt", "w");
        fprintf(f, "%s\n%.2f", player, score);
        fclose(f);
    } else {
        fscanf(f, "%s%f", name, &highscore);
        fclose(f);

        if (score > highscore) {
            f = fopen("highscore.txt", "w");
            fprintf(f, "%s\n%.2f", player, score);
            fclose(f);
            printf("\nNew highscore set by %s!\n", player);
        } else {
            printf("\nYour score didn't beat the highscore.\n");
        }
    }
}
