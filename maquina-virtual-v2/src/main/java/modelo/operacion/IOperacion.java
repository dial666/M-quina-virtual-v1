/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package modelo.operacion;

import modelo.UnidadIO;
import modelo.excepciones.VMException;
import modelo.operando.Operando;

/**
 *
 * @author valen
 */
public interface IOperacion
{
   public void ejecutar(Operando opA, Operando opB, UnidadIO mv) throws VMException; 
}
