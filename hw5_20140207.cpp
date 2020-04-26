#include <stdio.h>
#define MAX_STACK_SIZE 50

typedef struct {
    short int vert;
    short int horiz;
    }offsets;
offsets move[8];

typedef struct {
    short int row;
    short int col;
    short int dir;
    }element;
element stack[MAX_STACK_SIZE];
int top;

void push(element);
element pop();

int main(){
    FILE *ifile;
    int input,i,j,MAX_ROW, MAX_COL;
    int TRUE =1, FALSE = 0;
    move[0].vert = -1; move[0].horiz = 0; move[1].vert = -1; move[1].horiz = 1;
    move[2].vert = 0; move[2].horiz = 1; move[3].vert = 1; move[3].horiz = 1;
    move[4].vert = 1; move[4].horiz = 0; move[5].vert = 1; move[5].horiz = -1;
    move[6].vert = 0; move[6].horiz = -1; move[7].vert = -1; move[7].horiz = -1;
    //파일을 찾을 수 없으면 에러메세지 출력
    ifile = fopen("maze.txt","r");
    if (ifile == NULL){
        printf("File can not be found!!\n");
        return 1;
    }
    //maze.txt에서 첫 번째 줄 maze size를 scan 해온다
    input = fscanf(ifile,"%d %d", &MAX_ROW, &MAX_COL);
    //maze 2차 배열과 mark 2차 배열을 생성해준다
    const int EXIT_ROW = MAX_ROW - 1; const int EXIT_COL = MAX_COL - 1;
    int maze[MAX_ROW][MAX_COL];
    int mark[MAX_ROW][MAX_COL];
    //maze.txt에서 maze를 scan 해온다
    for(i=0;i<MAX_ROW;i++){
        for(j=0;j<MAX_COL;j++){
            input = fscanf(ifile,"%d",&maze[i][j]);
            if (input == EOF) break;
        }
    }
    
    int row = 0, col = 0, nextRow, nextCol, dir, found = FALSE;
    element position;
    mark[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
    //stack이 empty가 아니고 path를 찾지 못하였을때
    while (top > -1 && !found) {
        position = pop();
        row = position.row; col = position.col; dir = position.dir;
        while (dir < 8 && !found) {
            // dir 방향쪽으로 움직인다
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            //만약 row와 col이 EXIT_ROW EXIT_COL에 도착했을시, found = true로 바꿔준다
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
                found = TRUE;
            //도착하지 못하였을때
            else if (!maze[nextRow][nextCol] && !mark [nextRow][nextCol]) {
                mark [nextRow][nextCol] = 1;
                //현재 위치를 position에 넣어준다
                position.row = row; position.col = col;
                position.dir = ++dir;
                push(position);
                //새로운 위치를 넣어주고 북쪽에서 부터 다시 search한다
                row = nextRow; col = nextCol; dir = 0;
            }
            else ++dir;
        }
    }
    //만약 path가 존재한다면
    if (found) {
        printf("The path is : \n");
        printf("row col \n");
        for (i = 0; i <= top; i++){
            printf("%2d%5d", stack[i].row, stack[i].col);
        }
        printf("%2d%5d\n", row, col);
        printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
    }
    //만약 path가 존재하지 않는다면
    else printf("-1\n");
}


//push 함수
void push(element item){
    top += 1;
    stack[top] = item;
    return ;
}
//pop 함수
element pop(){
    element item;
    item = stack[top];
    top -= 1;
    return item;
}

