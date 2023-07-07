<p align='center'>
  <img width='200' heigth='225' src='https://user-images.githubusercontent.com/62605744/171186764-43f7aae0-81a9-4b6e-b4ce-af963564eafb.png'>
</p>

# CG_Project
Computer Graphics Project UV 2023-l

## Authors
- David Alberto Guzmán
- Mauricio Antonio Carrillo

## Instrucciones de instalación
1. Descargar e instalar C++
2. Descargar e instalar Visual Studio 2019 (No code) con funcionalidad para compilar C++.
3. Descargar las librerias de C++ que están en la rama correspondiente.
4. Definir la ruta para incluir los encabezados. (.h)

Para ello damos clic derecho y nos vamos a las propiedades de nuestro proyecto.

![image](https://user-images.githubusercontent.com/62605744/231725249-7a947845-f8f8-4c77-8899-2663cbeea67d.png)

Luego, vamos a C/C++ -> General -> Directorios de inclusión adicionales.

![image](https://user-images.githubusercontent.com/62605744/231725418-584a598c-dea1-4433-9b93-2993ed6c9220.png)

Y agregamos las rutas.

![image](https://user-images.githubusercontent.com/62605744/231725780-b1eaad80-4291-4613-a978-a7a4d792f89b.png)

5. Definir la ruta para incluir las librerias. (.lib)

Hacemos lo mismo para definir la ruta de las librerias en Vinculador -> General -> Directorios de bibliotecas adicionales.

![image](https://user-images.githubusercontent.com/62605744/231726135-2039971a-8aaa-4f5b-ba86-76f842b2bc16.png)

6. Vincular las librerias.

Finalmente vamos a Vinculador -> Entrada -> Dependencias adicionales y escribimos las librerias que vamos a incluir, las cuales son las siguientes:

![image](https://user-images.githubusercontent.com/62605744/231726364-75b27b4b-d5ab-4dba-b474-31d5ef772c6b.png)

![image](https://github.com/Daga2001/Lab3_CG/assets/62605744/633d6e2e-59f0-4c3f-93a9-97e9f5727cde)

7. Compilar y ejecutar la solución. (.sln)

Se da clic sobre el botón que dice "Depurador local de Windows"

![image](https://user-images.githubusercontent.com/62605744/231726848-7ee4b067-c36b-42d5-9fd8-a011c8ff31e1.png)

Cuando se ejecute el programa la salida debe de ser similar a esta:
![image](https://github.com/Daga2001/CG_Project/assets/62605744/4def088c-757d-4b6b-8128-75a1dac596fe)

## Aclaraciones
- en la rama main se muestran archivos de c++ que muestran los algoritmos de rasterización vistos en clase en 3D.
- se deja en una rama distinta las librerias a utilizar para la implementación de la actividad práctica de este laboratorio.
- se recomienda tener paciencia durante la ejecución del programa, debido a que se hace uso de texturas y objetos pesados en 3D.
- la simulación hecha en c++, permite al usuario interactuar en un mundo semiabierto, es decir, puede moverse con el teclado y rotar la vista con el mouse.

## Requerimientos
- se requiere de las siguientes librerias o cabeceras (.h):
  - opengl32.lib
  - GLEW
  - GLFW 
  - GLM
  - ASSIMP
  - STB

  Se recomienda instalarlas para una arquitectura de 32 bits.
