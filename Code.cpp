#include <bits/stdc++.h> 
using namespace std; 
  
// Your location Latitude. 
#define lat1d 28.3670
  
// Your location Longitude. 
#define lon1d 79.4304
  
#define pi 3.14159265358979323846 
#define earth_radius 6371.0 
  
ifstream hospital_list ("Hospital.json"); 
ofstream out ("answer.json"); 
  
// Function to convert degree to radian. 
double degtorad(double deg) 
{ 
    return ( deg * pi / 180); 
} 
  
// Calculate distance  between 2 given locations  
// using Great Circle Distance Formula. 
double distanceEarth(double lat2d, double lon2d) 
{                  
    double lat1, lon1, lat2, lon2,  
           delta_lon, central_ang; 
    
    lat1 = degtorad(lat1d); 
    lon1 = degtorad(lon1d); 
    lat2 = degtorad(lat2d); 
    lon2 = degtorad(lon2d); 
  
    delta_lon = lon2 - lon1; 
      
    // great circle distance formula. 
    central_ang = acos ( sin(lat1) * 
                  sin(lat2) + cos(lat1) * 
                  cos(lat2) * cos(delta_lon) );  
                    
    return (earth_radius * central_ang); 
} 
  
// Structure which contains data and 
// functions for accessing and processing 
// data from the given customers.json file. 
struct json 
{ 
    //x is used to measure the size of the element of latitude_as_string array.
    //y is used to measure the size of the element of longitude_as_string array. 
    //m is used to measure the size of the element of id_as_string array.
    //n is used to measure the size of the element of name array.
    //f keeps count of " " " symbol.
    //fi keeps count of " : " symbol. 
    long long int length, i, j, x, y, m, 
                  n, f, fi, id[10000]; 
      
    char latitude_as_string[10000],  
         longitude_as_string[1000],  
         id_as_string[1000], name[1000]; 
      
    double lat2d, lon2d; 
      
    // To get each line of customers.json 
    // file as string. 
    string line; 
  
    // Function to check whether distance between 
    // 2 points is less than 250km or not. 
    void distance_calculator() 
    { 
        if (distanceEarth(lat2d, lon2d) <= 250.0000) 
        { 
            // Converting id to int format. 
            id[i] = atoll(id_as_string); 
            i++; 
            out << "{\"Contact_No.\": " << id[i - 1] <<  
                ", \"Name\": " << name << "}" << endl; 
        } 
    } 
   
    // approach is used to get JSON attributes. 
    void json_parser() 
    {                      
        if (hospital_list.is_open()) 
        { 
              
            while (getline(hospital_list, line)) 
            { 
                  
                f = 0; x = 0; y = 0; fi = 0; m = 0, n = 0; 
                length = line.size(); 
  
                for (j = 0; j < length; j++) 
                { 
                      
                    if (line[j] == '"') 
                        f++; 
  
                    else if (line[j] == ':') 
                        fi++; 
                          
                    // To get latitude of the location.     
                    if (f == 3) 
                    { 
                        j++; 
  
                        while (line[j] != '"') 
                        { 
                            latitude_as_string[x] = line[j]; 
                            x++; j++; 
                        } 
  
                        j--; latitude_as_string[x] = '\0'; 
                    } 
                      
                    // To get longitude of the location. 
                    else if (f == 13) 
                    { 
                        j++; 
  
                        while (line[j] != '"') 
                        { 
                            longitude_as_string[y] = line[j]; 
                            y++; j++; 
                        } 
  
                        j--; longitude_as_string[y] = '\0'; 
                    } 
                      
                    // To get contact of the Hospital. 
                    if (fi == 2) 
                    { 
                        j += 2; 
  
                        while (line[j] != ',') 
                        { 
                            id_as_string[m] = line[j]; 
                            m++; j++; 
                        } 
  
                        j--; id_as_string[m] = '\0'; 
                        fi++; 
                    } 
                      
                    // To get Name of the Hospital. 
                    else if (fi == 4) 
                    { 
                        j += 2; 
  
                        while (line[j] != ',') 
                        { 
                            name[n] = line[j]; 
                            n++; j++; 
                        } 
  
                        j--; name[n] = '\0'; 
                        fi++; f += 2; 
                    } 
                } 
  
                // Converting latitude and longitude 
                // in string to float. 
                lat2d = atof(latitude_as_string); 
                lon2d = atof(longitude_as_string); 
                distance_calculator(); 
            } 
        } 
          
        // closing stream of hospital's file. 
        hospital_list.close(); 
          
        // closing stream of answer's file. 
        out.close(); 
    } 
}; 
  
int main() 
{ 
    // Creating object of the structure json 
    json obj; 
      
    // To read customers.json file. 
    obj.json_parser(); 
    return 0; 
} 