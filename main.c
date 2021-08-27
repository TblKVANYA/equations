//Воробьев Иван
//27.08.2021
//Копирование разрешено, если глазам не больно

//! @file main.c

//! @mainpage
//! main.c
//! \author Vorobev Ivan
//! \data 27.08.2021


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
//Опциональность программы: если переменная DEBUG определена,программа будет выполнять тест,
//иначе - решение с введенными данными
//#define  DEBUG //раскоментить, чтобы перейти в режим тестирования программы

#ifdef DEBUG
#    define RUNNING_PROG test_solving()//название основной функции, выолняющей тестирование
#else
#    define RUNNING_PROG solve_equations()//название основной функции, взаимодействующей с пользователем
#endif

/*!
 * функция, которая работает с пользователем
 * @return код ошибки
 */
int solve_equations();


//!значения кодов ответов и ошибок, получаемые и при тесте, и пользователем
enum answer{unknown, //!< нулевое значение, не должно возвращаться
        quad_0sol,//!<квадратное уравнение, не имеет решений
        quad_1sol,//!<квадратное уравнение, одно решение
        quad_2sol, //!<квадратное уравнение, 2 решения
        lin_0sol, //!<линейное уравнение, нет решений
        lin_1sol, //!<линеное уравнение, 1 решение
        lin_endless, //!<уравнение вида 0*х*х + 0*х + 0 = 0
        mis_a, //!< ошибка в передаче значения первого коэффициента в solving()
        mis_b, //!< ошибка в передаче значения второго коэффициента в solving()
        mis_c, //!< ошибка в передаче значения третьего коэффициента в solving()
        mis_x1x2//!< ошибка в передаче адреса для записи ответа в solving()
};

//! 11 - код ошибки передачи указателя на NULL в get_coefficients
#define NULL_ADDRESS 11

//!12 - код ошибки передачи одинаковых указателей в get_coefficients
#define SAME_ADDRESS 12

//!13 - код ошибки при неудачных тестах
#define UNSUCCESS_TEST 13

//!код ошибки при ошибочной инициализации тестовых структур
#define INITIALIZATION_ERROR 14

//!код ошибки при передаче первого неверного значения в result_printing()
#define PRINTING_X1 15

//!код ошибки при передаче второго неверного значения в result_printing()
#define PRINTING_X2 16

/*!
 * Производит ввод данных от пальзователя
 * @param *a, *b, *c указатели на адреса коэффициентов
 * @return код ошибки(при наличии)
 */
int get_coefficients(double *a, double *b, double *c);

/*! Выводит результаты пользователю, если приложение сработало без ошибок
 * @param switch_code код ответа
 * @param x1 значение х1
 * @param x2 значение x2
 * @return код ошибки(при наличии)
 */
int result_printing(int, double, double);

/*!
 * Выполняет запуск теста
 * /return код ошибки
 *
 *
 */
int test_solving();

//!объявление структуры, в которой будут входные данные и полученные тестами ответы
struct test_arr{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    int switch_code;//код ответа
};

//!объявление структуры, в которой будут храниться правильные ответы на тесты
struct exp_ans{
    double x1;
    double x2;
    int switch_code;//код ответа
};

//!количество тестов,которые программа будет проходить
#define tests_number 8

//!входные данные и полученные ответы для сравнения с правильными
struct test_arr input[tests_number];

//!правильные ответы на тесты: х1, х2 и код ответа
struct exp_ans answers[tests_number];

/*!
 * выполняет инициализацию вводных данных для тестирования
 * @return код ошибки
 */
int structure_initializer();

/*!
 * инициализирует структуру вводимых в тест данных и получаемых ответов
 * @param i номер теста
 * @param a первый коэффициент
 * @param b второй коэффициент
 * @param c третий коэффициент
 * @return код ошибки
 */
int input_initializer(int i, double a, double b, double c);

/*!
 * инициалзирует структуру справильными ответами
 * @param i номер теста
 * @param x1_init первый ответ
 * @param x2_init второй ответ
 * @param switch_init код ответа
 * @return
 */
int answer_initializer(int i, double x1_init, double x2_init, int switch_init);



//функции, задействованные и тестировщиком, и пользовательским приложением
/*!
 * решает уравнения
 * @param a первый коэффициент
 * @param b второй коэффициент
 * @param c третий коэффициент
 * @param x1 указатель на первый ответ
 * @param x2 указатель на второй ответ
 * @return код ответа или код ошибки
 */
int solving(double a, double b, double c, double *x1, double *x2);

/*!
 * решает квадратное уравнение
 * @param a первый коэффициент
 * @param b второй коэффициент
 * @param c третий коэффициент
 * @param x1 указатель на первый ответ
 * @param x2 указатель на второй ответ
 * @return код ответа
 */
static int solving_quadratic(double a, double b, double c, double *x1, double *x2);

/*!
 * решает линейные уравнения
 * @param b первый коэффициент
 * @param c свободный коэффициент
 * @param x указатель на ответ
 * @return код ответа или код ошибки
 */
static int solving_lin(double b, double c, double *x);

/*!
 * проверяет равенство значений с учетом погрешности
 * @param a первое сравниваемое значение
 * @param b второе сравниваемое значение
 * @param err_rate погрешность
 * @return равны ли значения
 */
int cmp_with_error(double a, double b, double err_rate);

//!значение погрешности для этой программы
const double ERROR_RATE =0.000001;

/*!
 * выводит ошибку, если передан ее код
 */
void print_error(int);

/*!
 * запускает всю программу, в зависимости от ifdef вызывает тестировщик или пользовательскую программу
 * @return 0
 */
int main() {
    int result_code = 0;//переменная, указывающая на наличие ошибок в приложении

    result_code = RUNNING_PROG;//вызываем тест либо пользовательскую функцию

    if (result_code != 0)//обе подфункции возвращают 0, если сработали корректно
        print_error(result_code);//вывод ошибки


    return 0;
}



int solve_equations(){
    printf("This programme is created to solve quadratic equation and linear\n");
    printf("Quadratic equation should look like a*x*x + b*x + c = 0\n");
    printf("If a = 0, the equation is linear\n\n");


    int ans_code = 0;
    double a=0, b=0, c=0;//вводимые величины
    ans_code = get_coefficients(&a, &b, &c);

    if (ans_code != 0)
        return ans_code;//при обнаружении ошибки сразу возвращаем ее в main

    printf("You have entered:\n");//предоставление пользователю введенных им значений
    printf("a = %lf, b = %lf, c = %lf\n", a, b, c);


    double x1=0, x2=0;
    enum answer switch_code = 0;
    switch_code = solving(a, b, c, &x1, &x2);

    if (switch_code >= 1 && switch_code <= 6){//switch_code из этих значений соотвестует коду решенного уравнения,
        // а не ошибки
        int ans_code = result_printing(switch_code, x1, x2);
        return ans_code;
    }
    else
        return switch_code;
}


int get_coefficients(double *a, double *b, double *c)
{
    //проверка на ошибки в аргументах
    if(a==NULL || b==NULL || c==NULL || a==b || b==c || a==c) {
        if (a==NULL || b==NULL || c==NULL)
            return NULL_ADDRESS;
        else
            return SAME_ADDRESS;
    }
    //окончание проверки

    printf("Enter coefficient connected to x*x:\n");
    while (scanf("%lf", a) != 1)
    {
        while (getchar() != '\n')
            ;
        printf("Enter one number\n");
    }

    printf("Enter coefficient connected to x:\n");
    while (scanf("%lf", b) != 1) {
        while (getchar() != '\n')
            ;
        printf("Enter one number\n");
    }

    printf("Enter coefficient unconnected to x:\n");
    while (scanf("%lf", c) != 1){
        while (getchar() != '\n')
            ;
        printf("Enter one number\n");
    }

    return 0;
}


int result_printing(int switch_code, double x1, double x2){
    //выполняем проверку отправленных аргументов
    if (isfinite(x1) == 0) {
        return(PRINTING_X1);//возвращаем ошибку
    }
    if (isfinite(x2) == 0){
        return PRINTING_X2;//возвращаем ошибку
    }
    //окончание проверки

    switch(switch_code){
        case quad_2sol://квадратное,2 корня
            printf("You have 2 solutions:\n");
            printf("x1 = %lf \nx2 = %lf \n", x1, x2);
            break;

        case quad_1sol://квадратное, 1 корень
            printf("You have the only solution: x = %lf\n", x1);
            break;

        case quad_0sol://квадратное, нет корней
            printf("This equation has no real solutions\n");
            break;

        case lin_endless://бесконечное кол-во решений при a=b=c=0
            printf("You entered every coefficient as a 0 and this equation has endless amount of solutions\n");
            break;

        case lin_1sol://линейное 1 решение
            printf("This isn't a quadratic equation,but the solution is %lf\n", x1);
            break;

        case lin_0sol: //линейное без решений
            printf("This non-quadratic equation has no real solutions\n");
            break;

        default://невозможен в конкретной программе, ф-ия вызывается только при уже обработанных аргументах switch
            printf("Mistake in solving function");
            break;
    }
    return 0;
}


int test_solving(){
    printf("The test is running\n\n");

    int ans_code = 0;


    ans_code = structure_initializer();//задаем тестовые данные

    if (ans_code == 0){//проверка, была ли ошибка в инициализации данных. Если не было, продолжает
        for (int i = 0; i < tests_number; i++){
            input[i].switch_code = solving(input[i].a, input[i].b, input[i].c, &input[i].x1, &input[i].x2);//получаем практические ответы

            if (cmp_with_error(input[i].x1, answers[i].x1, ERROR_RATE)==0 ||
                cmp_with_error(input[i].x2, answers[i].x2, ERROR_RATE)==0 ||
                input[i].switch_code != answers[i].switch_code) {//сравнение полученных значений и правильных

                ans_code = UNSUCCESS_TEST;//ставим значения ошибки, если она обнаружена
                //вывод ситуации, в которой произошла ошибка
                printf("Line #%d has not passed the test\n", i);
                printf("Coefficients: %lf, %lf, %lf\n", input[i].a, input[i].b, input[i].c);
                printf("Expected answers: %lf, %lf, %d\n", answers[i].x1, answers[i].x2, answers[i].switch_code);
                printf("Received answers: %lf, %lf, %d\n", input[i].x1, input[i].x2, input[i].switch_code);
            }
        }
    }

    if (ans_code == 0)
        printf("Test was successful\n");
    return ans_code;
}


int structure_initializer(){
    int err_code = 0;

    for (int i = 0; i < tests_number; i++)
    {
        input[i].switch_code = 0;
        input[i].x1 = input[i].x2 = 0.0;//значения, для получения которых нужно решить уравнение
        //ставим их начальное значение в 0
    }
    //при обнаружении ошибок увеличиваем значение переменной, отвечающей за них
    err_code += input_initializer(0, 0, 0, 0);//                          0*x*x + 0*x + 0 = 0
    err_code += answer_initializer(0, 0, 0, lin_endless);//  решений бесконечное число

    err_code += input_initializer(1, 0, 8, 9);//                          8x + 9 = 0
    err_code += answer_initializer(1, -1.125, 0, lin_1sol);//решение х = -1.125

    err_code += input_initializer(2, 0, 0, 9);//                          0*x + 9 = 0
    err_code += answer_initializer(2, 0, 0, lin_0sol);//     решений нет

    err_code += input_initializer(3, 2, 4, 2);//                          2*x*x + 4*x+ 2 = 0
    err_code += answer_initializer(3, -1, 0, quad_1sol);//   решение х = -1

    err_code += input_initializer(4, 5, 3, 1);//                          5*x*x + 3*x + 1 = 0
    err_code += answer_initializer(4, 0, 0, quad_0sol);//    решений нет

    err_code += input_initializer(5, 2, -24, 70);//                       2*x*x - 24*x + 70 = 0
    err_code += answer_initializer(5, 7, 5, quad_2sol);//    решения 5 и 7

    err_code += input_initializer(6,-5, 15, 0);//                         -5*x*x + 15*x = 0
    err_code += answer_initializer(6, 0, 3, quad_2sol);//    решения 0 и 3

    err_code += input_initializer(7, 0, 5, 2);//                          5*x + 2 = 0
    err_code += answer_initializer(7, -0.4, 0, lin_1sol);//  решение х = -0.4

    err_code = (err_code>0) ? INITIALIZATION_ERROR : 0;//если выявлены ошибки, возвращаем код ошибки
    return err_code;
}


int input_initializer(int i, double a_init, double b_init, double c_init){
    if (isfinite(a_init) == 0 || isfinite(b_init) == 0 || isfinite(c_init) == 0 || i < 0 || i >= tests_number) {
        printf("input_initializer with i = %d doesn't work\n", i);
        return 1;//указываем на ошибку в инициализации
    }
    //присваивание значений
    input[i].a = a_init;
    input[i].b = b_init;
    input[i].c = c_init;

    return 0;
}


int answer_initializer(int i, double x1_init, double x2_init, int switch_init) {
    if (isfinite(x1_init) == 0 || isfinite(x2_init) == 0 || switch_init < 0 || switch_init > 6 || i < 0 ||
        i >= tests_number) {
        printf("answer_initializer with i = %d doesn't work\n", i);
        return 1;//указываем на ошибку в инициализации
    }
    //присваивание значений
    answers[i].x1 = x1_init;
    answers[i].x2 = x2_init;
    answers[i].switch_code = switch_init;

    return 0;
}



int solving(double a, double b, double c, double *x1, double *x2){
    //проверка правильности введенных данных, если они неверны, программа сразу возвращает ошибку
    if (isfinite(a) == 0){
        printf("first coefficient sent incorrect\n");
        return mis_a;
    }
    if (isfinite(b) == 0){
        printf("second coefficient sent incorrect\n");
        return mis_b;
    }
    if (isfinite(c) == 0){
        printf("third coefficient sent incorrect\n");
        return mis_c;
    }
    if (x1 == x2 || x1 == NULL || x2 == NULL){
        printf("Incorrect address in solving\n");
        return mis_x1x2;
    }
    //проверка окончена, если она успешна, переходим к вычислению


    int switch_code = 0;

    if (cmp_with_error(a, 0, ERROR_RATE)==0)
        switch_code = solving_quadratic(a, b, c, x1, x2);//вызывает решение квадратного уравнения, если уравнение квадратное
    else
        switch_code = solving_lin(b, c, x1);//вызывает решение линейного уравнения

    return  switch_code;
}


static int solving_quadratic(double a, double b, double c, double *x1, double *x2){
    int switch_code = 0;
    double D = b*b - (4*a*c);

    if (D >= 0)
        if (cmp_with_error(D, 0, ERROR_RATE) == 1) {
            *x1 = (-1)*b / (2 * a);
            switch_code = quad_1sol;
        }
        else {
            D = sqrt(D);
            *x1 = ( D-b) / (2 * a);
            *x2 = (-D-b) / (2 * a);
            switch_code = quad_2sol;
        }

    else
        switch_code = quad_0sol;

    return switch_code;
}


static int solving_lin(double b, double c,double *x){
    int switch_code = 0;

    if (cmp_with_error(b, 0, ERROR_RATE)==1 && cmp_with_error(c,0, ERROR_RATE)==1)
        switch_code = lin_endless;
    else
        if (cmp_with_error(b, 0, ERROR_RATE)==1)
            switch_code = lin_0sol;
        else {
            *x = (-1) * c/b;
            switch_code = lin_1sol;
        }
    return switch_code;
}



int cmp_with_error(double a, double b, double err_rate){

    if (isfinite(a) == 0){
        printf("cmp_with_error: incorrect first value\n");
        exit(EXIT_FAILURE);
    }
    if (isfinite(b) == 0){
        printf("cmp_with_error: incorrect second value\n");
        exit(EXIT_FAILURE);
    }
    if (isfinite(err_rate) == 0){
        printf("cmp_with_error: incorrect error_rate value\n");
        exit(EXIT_FAILURE);
    }

    return (fabs(a-b)<err_rate ? 1 : 0);
}


void print_error(int error_code){
    switch(error_code)
    {
        //ошибки из solving() функции
        case mis_a:
            printf("first coefficient wasn't send to solving() correctly\n");
            break;
        case mis_b:
            printf("second coefficient wasn't send to solving() correctly\n");
            break;
        case mis_c:
            printf("third coefficient wasn't send to solving() correctly\n");
            break;
        case mis_x1x2:
            printf("Answer pointers weren't send to solving() correctly\n");
            break;
        //ошибки в get_coefficients
        case NULL_ADDRESS:
            printf("NULL addresses in get_coefficients\n");
            break;
        case SAME_ADDRESS:
            printf("Same addresses in get_coefficients\n");
            break;
        //ошибки в тестовой функциии
        case UNSUCCESS_TEST:
            printf("Programme was in test mode and it didn't work\n");
            break;
        case INITIALIZATION_ERROR:
            printf("Programme was in test mode and it cannot initialize values\n");
            break;
        //ошибки из printing_result()
        case PRINTING_X1:
            printf("Incorrect value as x1 in printing_result()\n");
            break;
        case PRINTING_X2:
            printf("Incorrect value as x2 in printing_result()\n");
            break;
        default://неизвестная ошибка
            printf("Your value of error_code: %d\n", error_code);
            printf("Check your main function\n");
            assert(0);
    }
}
