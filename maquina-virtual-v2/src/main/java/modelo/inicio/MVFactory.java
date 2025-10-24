/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package modelo.inicio;

import modelo.inicio.IInicializadorMV;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.util.Arrays;
import modelo.CreadorVMI1;
import modelo.IMaquinaVirtual;
import modelo.MaquinaVirtual;
import modelo.Memoria;
import modelo.Registros;
import modelo.TablaSegmentos;
import modelo.excepciones.VMException;

/**
 *
 * @author valen
 */
public class MVFactory
{
    private String archVmi;
    private String archVmx;
    private int tamMemoria;
    private String[] params;
    private boolean disassembler;
    private IInicializadorMV inicializador;
    
    public MVFactory()
    {
        this.tamMemoria = 16 * 1024;
    }
    
    protected void interpretarArgs(String[] args)
    {
        int i = 0;
        int argc = args.length;
        while (i < argc)
        {
            if (args[i].endsWith(".vmx"))
                this.archVmx = args[i];
            else
                if (args[i].endsWith(".vmi"))
                    this.archVmi = args[i];
                else
                    if (args[i].equals("-d"))
                        this.disassembler = true;
                    else
                        if (args[i].startsWith("m="))
                            this.tamMemoria = Integer.parseInt(args[i].substring(2)) * 1024;
                        else
                            if (args[i].equals("-p"))
                            {
                                this.params = Arrays.copyOfRange(args, i + 1, argc);          
                                break;
                            }
            i++;
        }
        if (this.params == null)
            this.params = new String[0];
        
    }
    
    public IMaquinaVirtual creaMV(String[] args) throws FileNotFoundException, IOException, VMException
    {
        IMaquinaVirtual mv = null;
        
        interpretarArgs(args);
        if (this.tamMemoria < 0)
            throw new VMException("tamanio de memoria invalido");
        
        if (this.archVmx != null || this.archVmi != null)
        {
            Memoria m = new Memoria(this.tamMemoria);
            Registros r = new Registros();
            TablaSegmentos t = new TablaSegmentos();
            ByteBuffer byteBufferArchivo = null;
            if (this.archVmx != null)
            {         
                InputStream inputStream = new FileInputStream(this.archVmx);
                byteBufferArchivo = ByteBuffer.wrap(inputStream.readAllBytes());
                inputStream.close();

                int version = byteBufferArchivo.get(5);
                this.inicializador = switch (version)
                {
                    case 1 -> new InicializadorMV1();
                    case 2 -> new InicializadorMV2();
                    default -> throw new VMException("version de archivo .vmx desconocida");
                };
            }
            else
                if (this.archVmi != null)
                {
                    InputStream inputStream = new FileInputStream(this.archVmi); 
                    byteBufferArchivo = ByteBuffer.wrap(inputStream.readAllBytes());
                    inputStream.close();
                    
                    this.inicializador = new InicializadorVMI1();
                }
            
            byteBufferArchivo.position(6);
            this.inicializador.inicializa(m, r, t, params, byteBufferArchivo.slice());
            mv = new MaquinaVirtual(m, r, t, this.disassembler, new CreadorVMI1(this.archVmi));
        }
        
        return mv;
    }
}
