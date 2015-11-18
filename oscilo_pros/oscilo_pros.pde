import processing.serial.*;  // EMPIEZA CONEXION ARDUINO

Serial puerto;          // 
int X, Y, Xu, Yu, i;    // Declaración de alguna variables

void setup()
{
  size(920,570);             // Tamaño de la pantalla del osciloscopio
  frameRate(1000);           // 
  println(Serial.list());    // Imprime en pantalla
  puerto = new Serial(this,Serial.list()[0], 9600);  //seleccion el puerto usb(COM en windows -_-) con el que va a trabajar
  puerto.bufferUntil('\n');  //
  background(#006666);       // Inicia el fondo de pantalla en un color en este caso se decidio un codigo exadecimal que para que funcione se debe poner el simbolo # al inicio
  X= width +20;              // Hace que empiece al inicio del recuadro blanco
}

void draw()
{
  strokeWeight(1);      //da el ancho a las lineas de GRILLAS
  for(i=0;i<=21;i++)    // ciclo for que permitira definir el color negro por toda la cuadricula de la pantalla
  {
    stroke(0,0,0);      //da el color(negro) a la cuadricula
    if(i<=20)
    {
		text(40-i,25,15+i*27.5);    //genera los numeros de la linea vertical de 20 a 40
    }
 
   
    line(20,10+i*27.5,width-20,10+i*27.5);    // lineas horizontales cada 27.5 px por el tamaño definido de la pantalla
   
  }
  for(i=0;i<=32;i++) 
  {
	line(20+i*27.5,height-10,20+i*27.5,10);      //lineas verticales cada 27.5 px
  }
 
  stroke(255,255,255);          //color del bordado el stroke no afecta los text
  noFill();                     //si no esta, la pantalla se pone mal...
  rect(20,10,width-40,height-20);        //da el efecto del bordeado blanco
  line(20,height-10,20,10);    //linea vertical del eje y
  String inString = puerto.readStringUntil('\n'); //lectura puerto serial
  
  if(inString != null) 
  {
	inString = trim(inString);     //limpia espacios en blanco
    float dato = float (inString); //String a Float
    println(dato);                 //Imprime datos en consola
    dato= map(dato,20.7,40,37.5,height-37.5);   //Mapea los datos en un rango de pixeles 
    Y = int(height-dato);                    //Cambia la posicion de Y segun los datos

    if (X > width-20)       //Si la posicion en X llega al final vuelve a comenzar y le resta 20 para que no sobre pase el recuadro blanco 
    {       
		background(#006666);  //cuando la pantalla refresca inicia con ese color
		X=20;                 //
		Xu=X;                 //
		Yu=Y;                 //
    }
    stroke(#66FF00);        //
    strokeWeight(2);        //
    line(Xu, Yu, X, Y);     //linea entre la coordenada anterior y la coordenada actual
    
    Xu= X;
    Yu= Y;    
    X=5+X;
  }
}
