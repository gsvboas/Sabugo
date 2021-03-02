#ifndef CPU_DATA_H_
#define CPU_DATA_H_

typedef enum Primitive
{
    TRIANGLES = 0,
    TRIANGLE_FAN
} Primitive;

typedef enum AttributeTypeID
{
    FLOAT = 0
} AttributeTypeID;

typedef struct Attribute
{
    AttributeTypeID type;
    unsigned int length;
    unsigned int offset;
} Attribute;

typedef struct DataLayout
{
    Attribute* attributes;
    unsigned int attributes_count;
} DataLayout;

typedef struct Vertex
{
    float pos[2];
    float color[4];
} Vertex;


#endif

