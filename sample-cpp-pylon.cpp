#include <pylon/PylonIncludes.h>
#include <iostream>

using namespace Pylon;
using namespace GenApi;
using namespace std;

int main() {
    // Initialize the Pylon runtime system
    PylonInitialize();

    try {
        // Create a camera object and attach to the first available camera
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

        // Start the camera
        camera.Open();
        camera.StartGrabbing();

        // Grab and process images
        for (int i = 0; i < 10; ++i) {
            // Wait for the next image
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Check if the image is valid
            if (ptrGrabResult->GrabSucceeded()) {
                // Access the image data
                const uint8_t* pData = static_cast<const uint8_t*>(ptrGrabResult->GetBuffer());
                int width = ptrGrabResult->GetWidth();
                int height = ptrGrabResult->GetHeight();
                int pixelSize = ptrGrabResult->GetPixelSize();

                // Process the image data here...

                // Display the image size and pixel format
                cout << "Image width: " << width << endl;
                cout << "Image height: " << height << endl;
                cout << "Pixel format: " << ptrGrabResult->GetPixelType() << endl;
            }
        }

        // Stop the camera and close it
        camera.StopGrabbing();
        camera.Close();
    }
    catch (const GenericException& e) {
        cerr << "An exception occurred: " << e.GetDescription() << endl;
        return -1;
    }

    // Terminate the Pylon runtime system
    PylonTerminate();

    return 0;
}
