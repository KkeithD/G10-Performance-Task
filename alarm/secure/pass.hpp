/**
 * 
 *     /$$$$$$            /$$    /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$$$
 *    /$$__  $$         /$$$$   /$$$_  $$      | $$__  $$| $$_____/|__  $$__/
 *   | $$  \__/        |_  $$  | $$$$\ $$      | $$  \ $$| $$         | $$   
 *   | $$ /$$$$ /$$$$$$  | $$  | $$ $$ $$      | $$$$$$$/| $$$$$      | $$   
 *   | $$|_  $$|______/  | $$  | $$\ $$$$      | $$____/ | $$__/      | $$   
 *   | $$  \ $$          | $$  | $$ \ $$$      | $$      | $$         | $$   
 *   |  $$$$$$/         /$$$$$$|  $$$$$$/      | $$      | $$         | $$   
 *   \______/         |______/ \______/       |__/      |__/         |__/   
 *   
 *   By ~ Keith Davies.
 *   
 *   This is where the encrypted password is defined.
 *
 * ==========================================================================
 *                                Instructions                                
 * 
 *    1 - Go to https://www.movable-type.co.uk/scripts/sha256.html and type your
 *        password in the "Message" box.
 *
 *    2 - Copy the text from the "Hash" box and paste it in this file
 *        Your file should look like this. (Don't this example passwword)
 *
 *        #define SYSTEM_PASSWORD a1cdf9b86be063bced6916eb4bb31d600f234
 *
 *    3 - Save, and close file.
 *
 *    4 - Compile and run project.
 *
 *    This long list of letters and numbers is a scrambled version of your
 *    password. You can securely store it in this file without worry of it ever
 *    being discovered. 
 *
 *    The next time you disarm the alarm, your password is comapared to the encrypted
 *    password stored in this file. If it's a match, access is granted.
 * 
 *    Keep note that passwords are case sensitive, and can include only ASCII
 *    characters.
 */

#define SYSTEM_PASSWORD 46ba01f862cde3fab115f75550689216a7de7228b98476c29e7c19a27572315c * password = myg10project