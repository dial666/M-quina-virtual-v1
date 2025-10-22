/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

/**
 *
 * @author valen
 */
public class Memoria
{
    private byte[] memoria;
    
    public Memoria(int tamanio)
    {
        this.memoria = new byte[tamanio];
    }
    
    public int getValor(int dirFisica, int cantBytes)
    {
        int valor = 0;
        for (int i = 0; i < cantBytes; i++) 
            valor = (valor << 8) | (memoria[dirFisica + i] & 0xFF);
    
        valor = valor << (32 - 8*cantBytes);
        valor = valor >> (32 - 8*cantBytes);
        return valor;
    }
    
    public void setValor(int dirFisica, int cantBytes, int valor)
    {
         for (int i = 0; i < cantBytes; i++) 
         {
            int shift = 8 * (cantBytes - 1 - i);
            memoria[dirFisica + i] = (byte) ((valor >> shift) & 0xFF);
         }
    }
}
