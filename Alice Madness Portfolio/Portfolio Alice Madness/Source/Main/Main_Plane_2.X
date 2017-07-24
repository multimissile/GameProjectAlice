xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material PlayerMenuBackground_Mat {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "PlayerMenuBackground.tga";
 }
}

Frame Plane {
 

 FrameTransformMatrix {
  -0.000000,1.000000,0.000000,0.000000,-1.000000,-0.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh Plane {
  16;
  -0.000000;6.400000;-6.399999;,
  -0.000000;6.400000;-2.133333;,
  -0.000000;2.133333;-6.400000;,
  0.000000;2.133333;6.400000;,
  0.000000;2.133333;2.133333;,
  0.000000;6.400000;6.400000;,
  0.000000;6.400000;2.133333;,
  -0.000000;2.133333;-2.133333;,
  -0.000000;-2.133333;-6.400000;,
  -0.000000;-2.133333;-2.133333;,
  -0.000000;-6.400000;-6.400000;,
  -0.000000;-6.400000;-2.133334;,
  0.000000;-2.133333;2.133333;,
  0.000000;-6.400000;2.133333;,
  0.000000;-2.133333;6.400000;,
  0.000000;-6.400000;6.399999;;
  18;
  3;0,1,2;,
  3;3,4,5;,
  3;6,5,4;,
  3;4,7,6;,
  3;1,6,7;,
  3;7,2,1;,
  3;2,7,8;,
  3;9,8,7;,
  3;8,9,10;,
  3;11,10,9;,
  3;9,12,11;,
  3;13,11,12;,
  3;12,14,13;,
  3;15,13,14;,
  3;7,4,9;,
  3;12,9,4;,
  3;4,3,12;,
  3;14,12,3;;

  MeshMaterialList {
   1;
   18;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { PlayerMenuBackground_Mat }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   80;
   1065353216,
   673783109,
   3012357562,
   939524096,
   939524096,
   1065353216,
   667373622,
   3011697855,
   1051369472,
   939524096,
   1065353216,
   662547430,
   3012357561,
   939524096,
   1051369472,
   1065353216,
   668165268,
   3012357562,
   1065353216,
   1051369472,
   1065353216,
   665988237,
   3011697855,
   1059758080,
   1051369472,
   1065353216,
   670936037,
   3012357561,
   1065353216,
   939524096,
   1065353216,
   664602852,
   3011697854,
   1059758080,
   939524096,
   1065353216,
   663217468,
   3011697855,
   1051369472,
   1051369472,
   1065353216,
   668165270,
   3012357562,
   939524096,
   1059758080,
   1065353216,
   666299244,
   3011792100,
   1051369472,
   1059758080,
   1065353216,
   670936040,
   3012357562,
   939524096,
   1065353216,
   1065353216,
   664602853,
   3011697855,
   1051369472,
   1065353216,
   1065353216,
   663217468,
   3011697853,
   1059758080,
   1059758080,
   1065353216,
   667373622,
   3011697855,
   1059758080,
   1065353216,
   1065353216,
   662547432,
   3012357561,
   1065353216,
   1059758080,
   1065353216,
   673783109,
   3012357561,
   1065353216,
   1065353216;
  }
 }
}