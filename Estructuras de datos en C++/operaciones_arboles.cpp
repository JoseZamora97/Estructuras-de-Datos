#ifndef nullptr
#define nullptr NULL
#endif

template <typename ArbolBin>	// YA ESTA
int numNodosSoloHijoDchoVacio(ArbolBin a)
{	
	// Caso base: es vacio.
	if (a.esVacio())
		return 0;
	// Caso recursivo
	else
	{
		ArbolBin hi , hd;
		
		a.hijoIzquierdo(hi);
		a.hijoDerecho(hd);	
	
		if (hd.esVacio() && !hi.esVacio())
			return 1 + numNodosSoloHijoDchoVacio(hi);
		else 
			return numNodosSoloHijoDchoVacio(hi) + numNodosSoloHijoDchoVacio(hd);
	}		
}

template <typename ArbolBin>	// YA ESTA
void recorridoEnAnchuraIterativo(ArbolBin a, Lista<typename ArbolBin::Elemento>& recorrido)
{
	recorrido.vaciar();
	
	if(!a.esVacio())
	{
		Pila<ArbolBin> cola_arbol;
		typename ArbolBin::Elemento e;
		
		ArbolBin aux, hi, hd;	
		
		//Meto al arbol a en la cola para procesarlo.
		cola_arbol.apilar(a);
	
		while (!cola_arbol.esVacia())
		{
			//Actualizo aux para procesar el arbol siguiente.
			cola_arbol.cima(aux);
			cola_arbol.desapilar();	
			
			//Guardo la raiz al final de la lista.
			aux.raiz(e);
			recorrido.insertarFinal(e);
		
			//Accedo al hijo izquierdo y lo meto en la cola.
			aux.hijoIzquierdo(hi);
			if(!hi.esVacio())
			{
				cola_arbol.apilar(hi);
			}			
			//Accedo al hijo derecho y lo meto en la cola.
			aux.hijoDerecho(hd);
			if(!hd.esVacio())
			{
				cola_arbol.apilar(hd);
			}
									
			//Elimino el primero de la cola que ya está procesado.				
		}
	}         
}

template <typename ArbolBin>	// IMPLEMENTACION ITERATIVA
void elementosNivelK(ArbolBin a, int k, Lista<typename ArbolBin::Elemento>& nivel_k)
{		
	
	nivel_k.vaciar();
	
	if(!a.esVacio())
	{
		ArbolBin hi, hd, aux;
		Cola<ArbolBin> cola_arbol;
		Cola<int> cola_nivel;
	
		typename ArbolBin::Elemento e;	
	
		int nivelActual=1;
		int nivelSig;
	
		cola_arbol.insertar(a);
		cola_nivel.insertar(nivelActual);
	
		while(!cola_arbol.esVacia())
		{
			cola_arbol.primero(aux);
			cola_nivel.primero(nivelActual);
		
			if(nivelActual==k)
			{
				aux.raiz(e);
				nivel_k.insertarFinal(e);
			}
			else
			{
				nivelSig = nivelActual+1;
			
				aux.hijoIzquierdo(hi);
				if (!hi.esVacio())
				{
					cola_arbol.insertar(hi);				
					cola_nivel.insertar(nivelSig);
				}		
			
				aux.hijoDerecho(hd);
				if (!hd.esVacio())
				{
					cola_arbol.insertar(hd);
					cola_nivel.insertar(nivelSig);
				}
			}
											
			cola_arbol.eliminar();
			cola_nivel.eliminar();
		}
	}		
}

template <typename ArbolBin>	// YA ESTA
bool esCompleto(ArbolBin a)
{	
	// Caso Base: es vacio.
	if(a.esVacio())
	{
		return true;
	}
	// Caso Recursivo:
	else
	{
		ArbolBin hizq , hder;
		
		a.hijoDerecho(hder);
		a.hijoIzquierdo(hizq);

		if( numHojas(hder) != numHojas(hizq) )
			return false;		
		else
			return ( esCompleto(hder) && esCompleto(hizq) );		
	}
}
