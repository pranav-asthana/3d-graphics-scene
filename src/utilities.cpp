#include "utilities.h"

vector<GLfloat> getColorVector(glm::vec3 color, int size)
{
    GLfloat c[] = {color.x, color.y, color.z};
    vector<GLfloat> color_vector;
    for (int i = 0; i < size;)
    {
        for (int j = 0; j < 3; j++)
        {
            color_vector.push_back(c[j]);
            i++;
        }
    }
    return color_vector;
}

vector<GLfloat> joinColors(vector<GLfloat> c1, vector<GLfloat> c2)
{
    vector<GLfloat> color;
    color.reserve(c1.size() + c2.size());
    color.insert(color.end(), c1.begin(), c1.end());
    color.insert(color.end(), c2.begin(), c2.end());
    return color;
}
