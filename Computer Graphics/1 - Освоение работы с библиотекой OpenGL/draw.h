/*
 Здесь реализуются функции для ПРОРИСОВКИ
 */

#include <iostream>
#include <GL/freeglut.h>

#include <cmath>

/*
 mat_dif - цвет рассеянного отражения материала (прозрачность задаётся 4 параметром)
 mat_spec - цвет зеркального отражения материала
 mat_amb - цвет фонового отражения материала
 mat_shininess - коэффициент блеска
 */

namespace global {
extern float cam_xz_rotate;
extern float cam_y_rotate;
extern float cam_zoom;
extern bool light_flag;
extern bool fog_flag;
}

// список
GLuint model_list; //объявляем

// текстура
GLuint texture;

// параметры для nurb поверхности
GLUnurbsObj* theNurb;

const int size_numb_x = 4;
const int size_numb_y = 4;

GLfloat ctlpoints[size_numb_x][size_numb_y][3];
GLfloat knots[size_numb_x + size_numb_y] = {
    0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0
};

// материал nurb поверхности
float mat_dif_Nurb[] = {0.0f, 0.4f, 0.0f, 1.0f};
float mat_spec_Nurb[] = {0.0f, 0.4f, 0.0f};
float mat_amb_Nurb[] = {0.0f, 0.4f, 0.0f};
float mat_shininess_Nurb = 0.1f * 128;

// генерируем точки поверхности
void init_surface() {
    int m = 5; // расстояние между точками
    for (int y = 0; y < size_numb_y; y++) {
        for (int x = 0; x < size_numb_x; x++) {
            ctlpoints[y][x][0] = m * ((GLfloat)y - 1.5);
            ctlpoints[y][x][1] = m * ((GLfloat)x - 1.5);
            
            // выпуклости на поверхности
            if ((y == 1 ||y == 2) && (x == 1 || x == 2))
                ctlpoints[y][x][2] = 10.0;
        }
    }
    
    theNurb = gluNewNurbsRenderer(); //создаёт объект нюрбс
    //Управляйте свойствами объектов NURBS
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 5.0);//объект, Управление вершинами с сеткой для простого рендеринга(макс длина использ при методе выборки)
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);//Визуализация поверхности в виде многоугольника //
    gluNurbsProperty(theNurb, GLU_AUTO_LOAD_MATRIX, false);//используется для создания расчетной и отсекающей матриц для каждой кривой или поверхности NURBS.
}

// метериалы объектов (четверых)
float mat_dif_list[] = {0.9f, 0.9f, 0.9f, 1.0f};
float mat_spec_list[] = {0.9f, 0.9f, 0.9f};
float mat_amb_list[] = {0.9f, 0.9f, 0.9f};
float mat_shininess_list = 0.1f * 128;

// настройки света
// материал объекта для визуализации источника
float mat_dif_light[] = {0.9f, 0.9f, 0.0f, 1.0f};
float mat_spec_light[] = {0.9f, 0.9f, 0.0f};
float mat_amb_light[] = {0.9f, 0.9f, 0.0f};
float mat_shininess_light = 0.1f * 128;

// материал света
float matl_dif_light[] = {0.9f, 0.9f, 0.9f, 1.0f};

// перемещение света
float light_position_fraction = 0.02;
float light_position_radius = 10;
float light_tick = 0;
// центр вращения XYZ и W (если поставить не 0, то будет точечный источник света)
float light_position[3][4] = {
    {0.0, 5.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0, 0.0}
};

// функция для отображения и включения света
void set_light(GLenum name, GLfloat *light_position) {
    // материал света
    glLightfv(name, GL_DIFFUSE, matl_dif_light);
    glLightfv(name, GL_POSITION, light_position);
    glLightf(name, GL_SPOT_CUTOFF, 360);
    
    // материал объекта который визуализирует источник света
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_light);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif_light);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_light);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_light);
    
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glutSolidSphere(0.2, 32, 32);
    glTranslatef(-light_position[0], -light_position[1], -light_position[2]);
    
    // включаем свет
    glEnable(name);
}

// чтение и преобразование текстур
void generate_textures() {
    int width, height, nrChannels;
    unsigned char *data;
    
    data = stbi_load("texture.png", &width, &height, &nrChannels, 0);
    glGenTextures(1, &texture); //имена текстур создёт
    glBindTexture(GL_TEXTURE_2D, texture);//пнг привязали к переменной 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// метод фильтрации
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //создаёт двумерное изображение текстуры
}

// натсройки для тумана
GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
void fog_on() {
    glEnable(GL_FOG);                       // Включает туман (GL_FOG)
    glFogi(GL_FOG_MODE, GL_EXP);// Выбираем тип тумана
    glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
    glFogf(GL_FOG_DENSITY, 0.05f);          // Насколько густым будет туман
    glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
    glFogf(GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман
    glFogf(GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается.
}

// генерация объекта для списка
void generate_list() {
    model_list = glGenLists(1); //название = создание пустых списков, выделение места для списка и возр указатель на него, при вызов модлист выводится список
    
    glNewList(model_list, GL_COMPILE); //новый откомпл список отображения модел лист
    //название - модел лист(где хранится), показывает где список начинается и какой тип, гл компил - создаём список в памяти, чтобы постоянно не вычисляться
    
    
    //все команды для списка
    glEnable(GL_TEXTURE_2D); //2D - нанесение текстуры, маг/мин фильтр - подгонка под размер
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    model_cube();
    
    glScalef(0.5, 0.5, 0.5);//размер верх
    glTranslatef(0, 0, 3);
    model_cube();
    
    glScalef(2, 2, 2);//размер ниж
    glTranslatef(0, 0, -1.5);
    
    glDisable(GL_TEXTURE_2D);
    
    glEndList(); //Закончили создание списка
}

void Display(void) {
    glLoadIdentity();
    
    // рассчитываем передвижение для камеры
    move();
    
    // задаём параметры камере
    gluLookAt(
              cos(global::cam_y_rotate) * sin(global::cam_xz_rotate) * global::cam_zoom,
              sin(global::cam_y_rotate) * global::cam_zoom,
              cos(global::cam_y_rotate) * cos(global::cam_xz_rotate) * global::cam_zoom,
              0, 0, 0,
              0.0f, 1.0f, 0.0f
              );
    
    // фон
    glClearColor(0.7, 0.7, 0.7, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // без этого буквально все элементы становятся 3D (видно сквозь объекты)
    glEnable(GL_DEPTH_TEST);
    
    // включаем смешивание цвета (для прозрачности)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // туман
    if (global::fog_flag) glDisable(GL_FOG);
    else glEnable(GL_FOG);
    
    /* включаем освещение */
    glEnable(GL_LIGHTING);
    
    // перемещение испочников света
    if (global::light_flag) light_tick += light_position_fraction;
    float light_position_rotate[4];
    
    /* настриваем источники света */
    // крутится вокруг сцены (XZ)
    light_position_rotate[0] = light_position[0][0] + (cos(light_tick) * light_position_radius);
    light_position_rotate[1] = light_position[0][1];
    light_position_rotate[2] = light_position[0][2] + (sin(light_tick) * light_position_radius);
    set_light(GL_LIGHT0, light_position_rotate);
    
    // для того чтобы поверхность нормально реагировала на свет
    glEnable(GL_AUTO_NORMAL);
    
    // объекты
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_Nurb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif_Nurb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_Nurb);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_Nurb);
    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    
    // рисуем nurb поверхность
    gluBeginSurface(theNurb);//начниет описание поверхности
    gluNurbsSurface(theNurb,
                    size_numb_x + size_numb_y, knots, size_numb_x + size_numb_y, knots,
                    size_numb_x * 3, 3, &ctlpoints[0][0][0],
                    4, 4, GL_MAP2_VERTEX_3);
    //определяет форму нюрб поверхности
    //кнотс создабтся на 38 строке
    gluEndSurface(theNurb); //завершается создание нюрб поверхности
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb_list);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif_list);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec_list);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess_list);
    
    glTranslatef(10.0f, -5.0f, 1.0f);
    glCallList(model_list);
    
    glTranslatef(0.0f, 3.0f, 0.0f);
    glCallList(model_list);
    
    glTranslatef(0.0f, 3.0f, 0.0f);
    glCallList(model_list);
    
    glTranslatef(0.0f, 3.0f, 0.0f);
    glCallList(model_list);
    
    glPopMatrix();
    glFlush();
}

void Reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w / h, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}
