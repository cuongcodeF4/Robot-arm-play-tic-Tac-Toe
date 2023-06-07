n=3;
R=20; 
L=300;
l1=80;
l2=250;
l3=250;
Z=80;
clc
syms t1 t2 t3 t4 pi  A B xa xb ya yb 
for i=1:1:3
    for j=1:1:3       
        %DAU X
        if ((i==j)||(i+j==4))
            %Dau /
            for t=0:0.05:1
                xa= (L/n)*(i-1);
                xb= (L/n)*i;
                ya=(L/n)*(j-1);
                yb= (L/n)* j ;
               
    
                X =(xa+30) +(xb-xa-60)*t;   %giam kich thuoc chu x
                Y =(ya+30) +(yb-ya-60)*t; 

                t1 = atan2(Y,X);
                c1=cos(t1);
                s1= sin(t1);      
                A= X /c1;
                B= Z-l1;

                c3= ((A)^2 +(B)^2 -l2^2 - l3^2)/(2*l2*l3);
                s3 = sqrt(abs(1-c3^2));
                t3= atan2(s3,c3);

                c2= (A*(l2 +l3*c3 )+ B*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                s2 = (B*(l2+l3*c3)- A*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                t2= atan2(s2,c2);


                Px= cos(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Py= sin(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Pz= l1+l3*sin(t2+t3)+sin(t2)*l2;

                axis([0  300  0  300])
                axis square
                axis on
                
                rectangle('Position',[0 0 100 100]);
                rectangle('Position',[100 0 100 100]);
                rectangle('Position',[200 0 100 100]);
                rectangle('Position',[0 100 100 100]);
                rectangle('Position',[100 100 100 100]);
                rectangle('Position',[200 100 100 100]);
                rectangle('Position',[0 200 100 100]);
                rectangle('Position',[100 200 100 100]);
                rectangle('Position',[200 200 100 100]);

                plot(Px,Py,'--.'); pause(0.01);
                xlabel('Truc x')
                ylabel('Truc y')
                grid on
                hold on
            end
            
            
            %Dau \
            for t=0:0.05:1
                xa= (L/n)*(i-1);
                xb= (L/n)*i;
                ya=(L/n)*(j-1);
                yb= (L/n)* j ;

                X =(xa+30) +(xb-xa-60)*t; %giam kich thuoc chu x
                Y =(yb-30) +(ya-yb+60)*t; 

                t1 = atan2(Y,X);
                c1=cos(t1);
                s1= sin(t1);      
                A= X /c1;
                B= Z-l1;

                c3= ((A)^2 +(B)^2 -l2^2 - l3^2)/(2*l2*l3);
                s3 = sqrt(abs(1-c3^2));
                t3= atan2(s3,c3);

                c2= (A*(l2 +l3*c3 )+ B*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                s2 = (B*(l2+l3*c3)- A*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                t2= atan2(s2,c2);


                Px= cos(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Py= sin(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Pz= l1+l3*sin(t2+t3)+sin(t2)*l2;



                axis([0  300  0  300])
                axis square
                axis on    

                plot(Px,Py,'--.'); pause(0.01);
                xlabel('Truc x')
                ylabel('Truc y')
                grid on
                hold on
            end
        
            
            
            
            
            
        else
            %DAU 0
            for t=0:0.1:2*pi
                X0 = (L/n)*(i-0.5);
                Y0 = (L/n)*(j-0.5);

                X = X0+R*cos(t);
                Y = Y0+R*sin(t);

                t1 = atan2(Y,X);
                c1=cos(t1);
                s1= sin(t1);      
                A= X /c1;
                B= Z-l1;

                c3= ((A)^2 +(B)^2 -l2^2 - l3^2)/(2*l2*l3);
                s3 = sqrt(abs(1-c3^2));
                t3= atan2(s3,c3);

                c2= (A*(l2 +l3*c3 )+ B*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                s2 = (B*(l2+l3*c3)- A*l3*s3)/((l2+l3*c3)^2 +(l3*s3)^2);
                t2= atan2(s2,c2);


                Px= cos(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Py= sin(t1)*(l3*cos(t2+t3)+cos(t2)*l2);
                Pz= l1+l3*sin(t2+t3)+sin(t2)*l2;


                axis([0  300  0  300])
                axis square
                axis on
                
                plot(Px,Py,'--.'); pause(0.01);
                xlabel('Truc x')
                ylabel('Truc y')
                grid on
                hold on
            end
        end 
   end 
end
            
