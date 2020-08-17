#include<windows.h>
#include <GL/glut.h>

#include<bits/stdc++.h>
using namespace std;

#define PI acos(-1.0)  // 3.1415926535897932





int a = 0;
int  refreshMills = 1000;


double pol[7][6][2]={
    { {19.02,52.36},{18.13,51.35},{17.52,45.95},{18.24,44.96},{19.04,46},{19.66,51.28}},
    { {18.12,44.29},{17.24,43.28},{16.63,37.88},{17.35,36.89},{18.15,37.93},{18.77,43.21}},
    { {17.8,36.4},{18.66,35.81},{24.6,35.81},{25.39,36.59},{24.63,37.42},{18.66,37.42}},
    { {18.73,44.55},{19.34,43.64},{25.27,43.7},{26.11,44.52},{25.43,45.41},{19.47,45.45}},
    { {19.49,52.74},{20.18,51.74},{25.97,51.71},{26.87,52.6},{26.01,53.38},{20.38,53.42}},
    { {27.29,52.32},{26.41,51.31},{25.79,45.91},{26.51,44.92},{27.31,45.96},{27.94,51.24}},
    { {26.51,44.33},{25.63,43.32},{25.02,37.92},{25.79,37.02},{26.54,37.97},{27.16,43.25}}};
int digits[10][7];





/** Basic Circle Making Function **/

void circle(double r, double cx, double cy, double R, double G, double B, double O)
{
    glColor4d(R/255.0,G/255.0,B/255.0,O);
    glBegin(GL_POLYGON);
    for(int i =0 ; i <= 360 ; i ++)
        glVertex2d( cx +( cos(i*(PI/180.0))*r ), cy+( sin(i*(PI/180.0))*r ) );
    glEnd();
}




void init(void)
{
    /** For Opacity Enable **/
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,125, 0,60);
}



void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);


    circle(1,47,46,255,00,0, ( a&1 ? .1 : .9) );
    circle(1,46,38,255,00,0, ( a&1 ? .1 : .9) );
    circle(1,82,46,255,00,0, ( a&1 ? .1 : .9) );
    circle(1,81,38,255,00,0, ( a&1 ? .1 : .9) );






    time_t CLK = time(0);
    tm *clk = localtime(&CLK);






    /****************************************          Time          ***************************************************/

    int time[3] = {clk->tm_hour,clk->tm_min,clk->tm_sec};

    for(int p = 0 ; p < 3 ; p ++)
    {
        string A = "00";

        time[p]-= ( !p && time[p] > 12 ? 12 : 0 );
        
        if(p==0 && time[p]==0)time[p]=12;

        for(int t = 0 ; t < 2; t++){
            A[t]+=time[p]%10;
            time[p]/=10;
        }
        swap(A[0],A[1]);


        for(int k = 0 ; k < 2 ; k ++)
        {
            int B = A[k]-'0';
            for(int i = 0 ; i < 7 ; i ++)
            {

                glColor4d(195/255.0,60/255.0,0/255.0, ( !digits[B%10][i] || (!k && !B && !p) ? .08 : 1));

                glBegin(GL_POLYGON);
                for(int j = 0 ; j < 6 ; j ++)
                    glVertex2d(pol[i][j][0] + (p*35) + (k*13) -2 ,pol[i][j][1]-3  );
                glEnd();
            }
        }
    }







    /****************************************          Date          ***************************************************/




    int date[3]={clk->tm_mday , clk->tm_mon+1 , clk->tm_year+1900};

    for(int p = 0 ; p < 3 ; p ++)
    {
        string A = "0000";

        for(int t = 0 ; t < 4; t++){
            A[t]+=date[p]%10;
            date[p]/=10;
        }
        reverse(A.begin(),A.end());
        if(p!=2)A=A.substr(2,2);


        for(int k = 0 ; k < 2+(p==2 ? 2 : 0) ; k ++)
        {
            int B = A[k]-'0';
            for(int i = 0 ; i < 7 ; i ++)
            {

                glColor4d(1,0,0, ( !digits[B%10][i] || (!k && !B ) ? .08 : 1));

                glBegin(GL_POLYGON);
                for(int j = 0 ; j < 6 ; j ++)
                    glVertex2d( (pol[i][j][0] + (p*40) + (k*13))*0.7 + 3 + (p==2 ? 3 : 0) , (pol[i][j][1] -20 )*0.7-3 );
                glEnd();
            }
        }
    }











    a++;
    glutSwapBuffers();

}


void Timer(int value)
{
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}




void import_data()
{

    int temp[10][7] = { {1,2,3,5,6,7,7},{6,7,7,7,7,7,7},{2,3,4,5,6,6,6},{3,4,5,6,7,7,7},{1,4,6,7,7,7,7},{1,3,4,5,7,7,7},{1,2,3,4,5,7,7},{5,6,7,7,7,7,7},{1,2,3,4,5,6,7},{1,3,4,5,6,7,7}};;
    for(int i = 0 ; i < 10 ; i ++){
        for(int j = 0 ; j < 7 ; j ++)digits[i][j]=0;
        for(int j = 0 ; j < 7 ; j++)digits[i][temp[i][j]-1]=1;
    }
}





int main(int argc, char* argv[])
{
    import_data();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowPosition(60, 60);
    glutInitWindowSize(1250,600);
    glutCreateWindow("Digital Clock");

    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);

    init();
    glutMainLoop();


    return 0;
}
