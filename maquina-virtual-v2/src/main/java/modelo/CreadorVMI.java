/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo;

import java.io.FileNotFoundException;
import java.io.IOException;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public abstract class CreadorVMI
{
    String archVmi;
    
    public CreadorVMI(String archVmi)
    {
        this.archVmi = archVmi;
    }
    
    public String getArchVmi()
    {
        return archVmi;
    }
    
    public abstract void creaImagen(byte[] memoria, byte[] registros, byte[] tablaSegmentos) throws VMException, FileNotFoundException, IOException;
}
