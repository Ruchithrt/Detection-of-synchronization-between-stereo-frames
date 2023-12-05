#include<iostream>
#include<string>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<vector>
#include<opencv2/core.hpp>
#include<opencv2/imgproc/imgproc.hpp> // import no include errors 
#include<opencv2/core/core.hpp>       // import no include errors
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/opencv.hpp>

#define fps 30
#define height  1200
#define width  1920

using namespace cv;
using namespace std;

long long int atoi(string str)
{
    long long int result = 0;                                       //Stores and returns the integer converted value for str
    int i = 0;                                                      //just a current character pointer for string
    while (str[i])                                                 //Now traverse the entire string and convert it into integer
    {
        //If any character is not an integer then just return -1
        if (!(str[i] - '0' >= 0 && str[i] - '0' <= 9))
            return -1;
        //else just keep updating the result
        result = result * 10 + str[i] - '0';
        i++;
    }
    return result;
}

long long int TimestampExtract(long long int x) {
    string num_str = to_string(x);                                 // Convert the number to a string
    string result_str = num_str.substr(num_str.size() - 14);       // Extract the last 14 characters of num_str
    long long result = atoi(result_str);                           // Convert the result string back to a long long integer
    return result;

}

long long int FrameNoExtract(long long int x)
{
    string num_str = to_string(x);                                  // Convert the number to a string
    string result_str = num_str.substr(0, num_str.size() - 14);     // Extract the desired substring
    long long int result = atoi(result_str);                        // Convert the result string back to a long long integer
    return result;
}

float getMSSIM(const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);           // cannot calculate on one byte large values
    i2.convertTo(I2, d);
    Mat I2_2 = I2.mul(I2);        // I2^2
    Mat I1_2 = I1.mul(I1);        // I1^2
    Mat I1_I2 = I1.mul(I2);        // I1 * I2
    /*************************** END INITS **********************************/
    Mat mu1, mu2;   // PRELIMINARY COMPUTING
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2 = mu1.mul(mu1);
    Mat mu2_2 = mu2.mul(mu2);
    Mat mu1_mu2 = mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;
    Scalar mssim = mean(ssim_map); // mssim = average of ssim map
    /*for (int i = 0; i < 3; i++)
    {
       cout << "["<<mssim[i]<<"]" << " ";
    }
    cout << endl;*/
    float floatVal0 = static_cast<float>(mssim[0]);
    float floatVal1 = static_cast<float>(mssim[1]);
    float floatVal2 = static_cast<float>(mssim[2]);
    float avg = (floatVal0 + floatVal1 + floatVal2) / 3;
    return avg;

}

void raw_rgb_left(int z)
{
    string input_folder = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_input\\left";
    string output_folder = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_output\\left";
    for (int i = 0; i < z; i++)
    {
        {
            string input_path = input_folder + "\\LEFT_HAWK_IMAGE" + to_string(i + 1) + ".raw";

            ifstream f(input_path, ios::binary);
            vector<uint16_t> raw_image_data(width * height);
            f.read(reinterpret_cast<char*>(raw_image_data.data()), raw_image_data.size() * sizeof(uint16_t));

            Mat raw_image_mat(height, width, CV_16UC1, raw_image_data.data());
            Mat rgb_image;
            cvtColor(raw_image_mat, rgb_image, COLOR_BayerRG2RGB);

            string output_path = output_folder + "\\LEFT_HAWK_IMAGE" + to_string(i + 1) + ".png";
            imwrite(output_path, rgb_image);
        }
    }
}

void raw_rgb_right(int z)
{
    string input_folder = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_input\\right";
    string output_folder = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_output\\right";
    for (int i = 0; i < z; i++)
    {
         {
            string input_path = input_folder + "\\RIGHT_HAWK_IMAGE" + to_string(i + 1) + ".raw";

            ifstream f(input_path, ios::binary);
            vector<uint16_t> raw_image_data(width * height);
            f.read(reinterpret_cast<char*>(raw_image_data.data()), raw_image_data.size() * sizeof(uint16_t));

            Mat raw_image_mat(height, width, CV_16UC1, raw_image_data.data());
            Mat rgb_image;
            cvtColor(raw_image_mat, rgb_image, COLOR_BayerRG2RGB);

            string output_path = output_folder + "\\RIGHT_HAWK_IMAGE" + to_string(i + 1) + ".png";
            //imshow("RGB Image", rgb_image);
            imwrite(output_path, rgb_image);
        }
    }
}

int main()
{
    string left, right;
    vector<long long int> first;                                  //declaration of vector to store right timestamps
    vector<long long int> second;                                 //declaration of vector to store left timestamps
    vector<long long int> difference;
    vector<long float> meanssim;
    vector<int> flagvalue;
    string left_input = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_output\\left";
    string right_input = "C:\\Users\\Ruchith\\OneDrive\\Desktop\\nvidia\\raw_final\\raw_final\\sample_output\\right";
    int z = 0;

    ifstream coeff("timestamp.txt");                          //creating ifstream object to access txt file
    if (coeff.is_open())
    {
        string line;
        std::getline(coeff, line);

        while (!coeff.eof())
        {
            //extract everything before ',' and push into first vector
            std::getline(coeff, left, ',');
            first.push_back(atoi(left));
            //extract everything before '\n' and push into second vector
            std::getline(coeff, right, '\n');
            second.push_back(atoi(right));
            z += 1;
        }
        coeff.close();
    }
    else cout << "Unable to open file" << endl;
    for (int k = 0; k < z; k++)
    {
        difference.push_back(abs(first[k] - second[k]));
        if (difference[k] <= (1.0 / fps))
        {
            flagvalue.push_back(1);
        }
        else
        {
            flagvalue.push_back(0);
        }

    }
    cout << "the value of z " << z<<endl;
    raw_rgb_left(z);
    raw_rgb_right(z);
    for (int i = 0; i < z; i++)
    {
        string image_path1 = left_input + "\\LEFT_HAWK_IMAGE" + to_string(i + 1) + ".png";
        string image_path2 = right_input + "\\RIGHT_HAWK_IMAGE" + to_string(i + 1) + ".png";

        Mat image1 = imread(image_path1, IMREAD_COLOR);
        if (image1.empty())
            cout << "failed to open" << endl;
        else
            cout << "loaded Left no:" << i + 1 << endl;

        Mat image2 = imread(image_path2, IMREAD_COLOR);
        if (image2.empty())
            cout << "failed to open" << endl;
        else
            cout << "loaded Right no: " << i + 1 << endl;

        meanssim.push_back(getMSSIM(image1, image2));

    }


    cout << "left timestamp" << "\t\t" << "right timestamp " << "\t" << "timestamp difference" << "\t" << "SSIM value" << "\t" << "result" << endl;
    for (int k = 0; k <z ; k++)
    {
        if (flagvalue[k] == 1 && meanssim[k] >= 0.7)
        {
            cout << TimestampExtract(first[k]) << "\t\t" << TimestampExtract(second[k]) << "\t\t" << difference[k] << "\t\t\t" << meanssim[k] << "\t" << "Sync at frame  " << FrameNoExtract(first[k]) << endl;
        }
        else if (flagvalue[k] == 1 && meanssim[k] < 0.7)
        {
            cout << TimestampExtract(first[k]) << "\t\t" << TimestampExtract(second[k]) << "\t\t" << difference[k] << "\t\t" << meanssim[k] << "\t" << "Async at frame " << FrameNoExtract(first[k]) << endl;
        }
        else if (flagvalue[k] == 0 && meanssim[k] >= 0.7)
        {
            cout << TimestampExtract(first[k]) << "\t\t" << TimestampExtract(second[k]) << "\t\t" << difference[k] << "\t\t" << meanssim[k] << "\t" << "Async at frame " << FrameNoExtract(first[k]) << endl;
        }
        else
        {
            cout << TimestampExtract(first[k]) << "\t\t" << TimestampExtract(second[k]) << "\t\t" << difference[k] << "\t\t" << meanssim[k] << "\t" << "Async at frame " << FrameNoExtract(first[k]) << endl;
        }
    }

    return 0;
}
