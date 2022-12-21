#include <windows.h>

#include <gl\glut.h>

#include <gl\glu.h>

#include <gl\gl.h>

#include <iostream>

#include <cmath>

#include <string>

#include <MMSystem.h>

#include <fstream>

#define SPACEBAR 32

using namespace std;



struct ball {

    float x;

    float y;

    ball* next;

};



ball* head = new ball;

ball* tail = new ball;



ifstream input;

ofstream output;



float posx = 0.0f, posy = 0.0f, x;

const double PI = 3.1416;

char uname[] = { '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0' };



int score = 0, level = 1, numb = 0, numball = 1, lowestscore, attempt = 10;

string stscore, stlevel, stattempt, status = "menu", leadernames[20], leaderscores[10];
int ShootingArrow = false;

float position[] = { -0.95f, -0.92f , -0.91f , -0.89f , -0.87f , -0.85f , -0.83f , -0.81f ,-0.79f ,-0.77f ,-0.75f };



int shooting = false;


void background()

{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}



void text(string word, float xp, float yp, float red, float green, float blue)

{

    glColor3f(red, green, blue);

    glRasterPos2f(xp, yp);

    for (int i = 0; i < word.length(); ++i)

    {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]);

    }

}


void background2(int)

{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);





    stlevel = to_string(level);

    text(stlevel, -0.02f, -0.02f, 1.0f, 0.0f, 1.0f);



    glBegin(GL_LINES);

    glColor3f(1.0f, 0.0f, 1.0f);

    glVertex2f(-0.1f, 0.1f);

    glVertex2f(0.1f, 0.1f);



    glVertex2f(0.1f, 0.1f);

    glVertex2f(0.1f, -0.1f);



    glVertex2f(0.1f, -0.1f);

    glVertex2f(-0.1f, -0.1f);



    glVertex2f(-0.1f, -0.1f);

    glVertex2f(-0.1f, 0.1f);

    glEnd();

}



void fileInput()

{

    input.open("leaderboard.txt");



    if (input.fail())

    {

        output.open("leaderboard.txt");



        for (int i = 0; i < 10; i++)

        {

            output << "s" << " " << -1 << endl;

            leadernames[i] = "s";

            leaderscores[i] = "-1";

        }

    }

    else

    {

        for (int i = 0; i < 10; i++)

        {

            input >> leadernames[i] >> leaderscores[i];

        }

    }

    lowestscore = stoi(leaderscores[9]);

}

void fileOutput()

{

    output.open("leaderboard.txt");



    for (int i = 0; i < 10; i++)

    {

        output << leadernames[i] << " " << leaderscores[i] << endl;

    }

}



void Arrow(float x, float y, float red, float green, float blue)

{

    float numTriangle = 40;

    GLfloat radius = 20;

    GLfloat tPI = 2.0 * PI;


    glBegin(GL_TRIANGLES);

    glColor3f(0.6f, 0.3f, 0.0f);



    glVertex2f(posx, posy - 0.05);

    glVertex2f(posx + 0.3f, posy);

    glVertex2f(posx + 0.3f, posy - 0.1);



    glEnd();


}



void tostatwin(int)

{

    status = "start";

}



void TurnOffShooting(int) {
    ShootingArrow = false;
}

void display(void)

{

    if (status == "menu")

    {




        background();


        text("Kick The Balls", -0.28f, 0.6f, 0.0f, 1.0f, 1.0f);





        text("START", -0.1f, -0.1f, 1.0f, 1.0f, 0.0f);



        text("Leaderboard", -0.2f, -0.35f, 1.0f, 1.0f, 0.0f);




        text("Help", -0.065f, -0.6f, 1.0f, 1.0f, 0.0f);

    }

    else if (status == "start")

    {

        background();



        Arrow(0, 0, 1.0f, 1.0f, 0.0f);

        Arrow(-0.05f, 0.02f, 0.0f, 0.0f, 0.0f);

        Arrow(0.05f, 0.02f, 0.0f, 0.0f, 0.0f);



        if (ShootingArrow == true) {


            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);

            glVertex2f(posx, posy - 0.05);

            glVertex2f(-1.0, posy - 0.05);
            glEnd();
            glutPostRedisplay();

            glutTimerFunc(100, TurnOffShooting, 0);

        }





        for (ball* temp = head; temp != NULL; temp = temp->next)

        {





            glBegin(GL_LINE_LOOP);
            glColor3f(1.0f, 0.0f, 0.0f);

            for (int i = 0; i <= 360; i++) {
                float degInRad = i * 100000;
                glVertex2f((temp->x + (float)cos(degInRad) * 0.05f), temp->y + ((float)sin(degInRad) * 0.05f));
            }

            glEnd();
            shooting = false;

        }

        char lvlnbr = 0;

        text("SCORE: ", -1.0f, 0.9f, 1.0f, 0.0, 1.0f);

        stscore = to_string(score);

        text(stscore, -0.7f, 0.9f, 1.0f, 1.0, 1.0f);


        text("Attempt: ", -1.0f, 0.7f, 1.0f, 0.0f, 1.0f);

        stattempt = to_string(attempt);

        text(stattempt, -0.7f, 0.7f, 1.0f, 1.0, 1.0f);



        text("LEVEL: ", -1.0f, 0.8f, 1.0f, 0.0f, 1.0f);

        stlevel = to_string(level);

        text(stlevel, -0.7f, 0.8f, 1.0f, 1.0, 1.0f);

    }

    else if (status == "name")

    {

        background();



        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 1.0f, 1.0f);



        glVertex2f(-0.92f, -0.85f);

        glVertex2f(-0.78f, -0.92f);

        glVertex2f(-0.78f, -0.78f);



        glEnd();



        text("", -0.28f, 0.7f, 0.0f, 1.0f, 0.0f);



        text("Enter your name(up to 20 characters):", -0.6f, 0.1f, 0.0f, 1.0f, 0.0f);



        string username;



        for (int i = 0; i < numb; i++)

        {

            username += uname[i];

        }



        text(username, -0.25f, -0.1f, 0.0f, 1.0f, 0.0f);

        text("Enter to continue", -0.35f, -0.3f, 0.0f, 1.0f, 0.0f);



        glBegin(GL_LINES);

        glColor3f(1.0f, 0.0f, 0.0f);



        glVertex2f(-0.45f, 0.0f);

        glVertex2f(0.45f, 0.0f);



        glVertex2f(0.45f, 0.0f);

        glVertex2f(0.45f, -0.15f);





        glVertex2f(0.45f, -0.15f);

        glVertex2f(-0.45f, -0.15f);



        glVertex2f(-0.45f, -0.15f);

        glVertex2f(-0.45f, 0.0f);

        glEnd();



    }

    else if (status == "leaderboard")

    {

        background();




        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 1.0f, 1.0f);



        glVertex2f(-0.92f, -0.85f);

        glVertex2f(-0.78f, -0.92f);

        glVertex2f(-0.78f, -0.78f);



        glEnd();



        text("", -0.32f, 0.7f, 1.0f, 0.21f, 0.04f);



        for (int i = 0; i < 10; i++)

        {

            text(to_string(i + 1) + '.', -0.9f, 0.4f - 0.1 * i, 1.0f, 1.0f, 1.0f);

            if (leaderscores[i] != "-1")

            {

                text(leadernames[i], -0.5f, 0.4f - 0.1 * i, 1.0f, 1.0f, 1.0f);

                text(leaderscores[i], 0.3f, 0.4f - 0.1 * i, 1.0f, 1.0f, 1.0f);

            }

        }



    }

    else if (status == "lvup")

    {

        stlevel = to_string(level);

        background2(1);

        glutTimerFunc(2000, tostatwin, 0);



    }

    else if (status == "help")

    {

        background();



        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 1.0f, 1.0f);



        glVertex2f(-0.92f, -0.85f);

        glVertex2f(-0.78f, -0.92f);

        glVertex2f(-0.78f, -0.78f);



        glEnd();



        text("", -0.32f, 0.7f, 0.0f, 1.0f, 1.0f);

        text("How to play:", -0.9f, 0.4f, 1.0f, 1.0f, 0.0f);

        text("1. Use arrow keys to move your Arrow.", -0.9f, 0.2f, 1.0f, 1.0f, 1.0f);

        text("2. Kick All The Balls.", -0.9f, 0.0f, 1.0f, 1.0f, 1.0f);

        text("3. Every Kick will grant you an extra score point.", -0.9f, -0.2f, 1.0f, 1.0f, 1.0f);

        text("4. Beat your friends and be the 1st in the Leaderboard.", -0.9f, -0.4f, 1.0f, 1.0f, 1.0f);

    }

    glFlush();

}


bool collision(ball* temp)

{



    if ((temp->y >= posy - 0.20f && temp->y <= posy + 0.1f)) {

        if (shooting == true) {
            score++;
            temp->y = 1.0;

        }

        return shooting = false;

    }
    else
    {

        if (shooting == true) {

            attempt = attempt - 1;
            return shooting = false;
        }


    }


}



void addball(int)

{

    float yrand[] = { -1.3f,-1.4f,-1.5f,-1.6f,-1.7f,-1.8f,-1.9f,-2.0f,-2.1f,-2.2f,-2.3f,-2.4f,-2.5f,-2.6f,-2.7f,-2.8f,-2.9f,-3.0f,-3.1f,-3.2f,-3.3f,-3.4f,-3.5f };

    if (numball < level)

    {

        ball* temp = new ball;

        temp->next = NULL;

        temp->y = yrand[rand() % 20];

        temp->x = position[rand() % 9];



        if (head == NULL)

        {

            head = temp;

            tail = temp;

        }

        else

        {

            tail->next = temp;

            tail = temp;

        }

        numball++;

        glutTimerFunc(rand() % 800 + 300, addball, 0);

    }

}



void Leaderboardupdate()

{

    string tnames[20], tscores[10];

    int i = 0;



    while (stoi(leaderscores[i]) > score)  //string to integer

    {

        tnames[i] = leadernames[i];

        tscores[i] = leaderscores[i];

        i++;

    }

    string userName;



    for (int j = 0; j < numb; j++)

    {

        userName += uname[j];

    }



    tnames[i] = userName;

    tscores[i] = to_string(score);



    for (; i < 9; i++)

    {

        tnames[i + 1] = leadernames[i];

        tscores[i + 1] = leaderscores[i];

    }



    for (int i = 0; i < 10; i++)

    {

        leadernames[i] = tnames[i];

        leaderscores[i] = tscores[i];

    }

}



void valreset()

{

    for (int i = 0; i < 15; i++)

        uname[i] = '\0';


    attempt = 10;
    score = 0;

    numball = 0;

    level = 1;



    while (head != NULL)

    {

        ball* temp = head->next;

        delete head;

        head = temp;

    }



    posx = -0.8f;

    posy = -0.3f;

}



void idle()

{

    if (status == "start")

    {

        if (head == NULL)

            addball(0);





        for (ball* temp = head; temp != NULL; temp = temp->next)

        {

            level == 1 ? temp->y += 0.0003f : temp->y += 0.0003f * level / 2;

            collision(temp);

            if (attempt == 0)

            {

                if (score > lowestscore)

                {

                    status = "leaderboard";

                    Leaderboardupdate();

                    fileOutput();


                }

                else

                {

                    status = "menu";



                }

                valreset();

                break;

            }

        }



        if (head != NULL && head->y > 1.0f)

        {
            cout << "In If Here" << endl;
            ball* temp = head->next;

            delete head;

            head = temp;

            numball--;

            addball(0);

            if (score % 10 == 0 && score != 0)

            {

                level++;
                score++;
                attempt = attempt + 5;

                status = "lvup";

            }

        }

    }

    glutPostRedisplay();

}



void specialKeys(int key, int x, int y)

{

    if (status == "start")

    {

        switch (key)

        {

        case GLUT_KEY_DOWN:

            if (posy > -0.9f)

                posy -= 0.1f;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:

            if (posy < 1.0f)

                posy += 0.1f; glutPostRedisplay();

            break;

        case GLUT_KEY_LEFT:

            if (posx > 0.0f)

                posx -= 0.1f;
            glutPostRedisplay();
            break;

        case GLUT_KEY_RIGHT:

            if (posx < 0.7f)

                posx += 0.1f; glutPostRedisplay();

            break;

        }

    }

}

void mouse(int button, int state, int x, int y)

{

    int width = glutGet(GLUT_WINDOW_WIDTH);

    int height = glutGet(GLUT_WINDOW_HEIGHT);



    if (status != "lvup")

        if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)



            if (status == "menu")

            {

                if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)

                    if (x < (1.15 * width / 2) && x >(0.85 * width / 2) && y > (height / 2) && y < (1.15 * height / 2))

                    {

                        status = "name";

                    }

                    else if (x < (1.1 * width / 2) && x >(0.9 * width / 2) && y > (1.5 * height / 2) && y < (1.65 * height / 2))

                        status = "help";

                    else if (x < (1.25 * width / 2) && x >(0.75 * width / 2) && y > (1.25 * height / 2) && y < (1.4 * height / 2))

                        status = "leaderboard";

            }



            else if (status == "help" || status == "leaderboard" || status == "name")

                if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)

                    if (x < (0.25 * width / 2) && x >(0.05 * width / 2) && y > (1.75 * height / 2) && y < (1.95 * height / 2))

                        status = "menu";



    glutPostRedisplay();

}



void keyinput(unsigned char key, int x, int y)

{
    if (key == 32) {
        shooting = true;
        ShootingArrow = true;
        glutPostRedisplay();
    }


    if (status == "name")

        if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))

        {

            if (numb < 20)

            {

                uname[numb] = key;

                numb++;

            }

        }

        else if (key == 13 && numb > 0)

            status = "start";

        else if (key == 8 && numb > 0)

        {

            numb--;

            uname[numb] = '\0';

        }



    glutPostRedisplay();

}



int main(int argc, char** argv)

{

    fileInput();

    srand(time(NULL));



    ball* temp = new ball;

    temp->next = NULL;

    temp->y = -1.0f;

    temp->x = position[rand() % 9];

    head = temp;

    tail = temp;

    glutInit(&argc, argv);



    glutInitWindowSize(600, 600);

    glutInitWindowPosition(390, 60);

    glutCreateWindow("Kick Balls");

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutIdleFunc(idle);

    glutDisplayFunc(display);

    glutMouseFunc(mouse);

    glutKeyboardFunc(keyinput);



    glutTimerFunc(rand() % 800 + 500, addball, 0);



    glutSpecialFunc(specialKeys);



    glutMainLoop();

}
