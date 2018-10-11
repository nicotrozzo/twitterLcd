#include "twUser.h"
#include "json.hpp"

using json = nlohmann::json;

#define API_KEY "HCB39Q15wIoH61KIkY5faRDf6"
#define API_SKEY "7s8uvgQnJqjJDqA6JsLIFp90FcOaoR5Ic41LWyHOic0Ht3SRJ6"

twUser::twUser()
{
	API_key = API_KEY;
	API_SecretKey = API_SKEY;
	curl = curl_easy_init();
	if (curl)
	{
		//Seteamos primero la pagina donde nos vamos a conectar. Para buscar el token es siempre la misma
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.twitter.com/oauth2/token");

		// Si la p�gina nos redirije a alg�n lado, le decimos a curl que siga dicha redirecci�n.
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		// Le decimos a CURL que trabaje tanto con HTTP como HTTPS, Autenticaci�n por HTTP en modo b�sico.
		curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);
		curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);

		//Preparamos el password para la autenticaci�n
		string userPwd = API_key + ":" + API_SecretKey;
		//Se lo seteamos a CURL.
		curl_easy_setopt(curl, CURLOPT_USERPWD, userPwd.c_str());

		struct curl_slist *list = NULL;

		//Le decimos a CURL que vamos a mandar URLs codificadas y adem�s en formato UTF8.
		list = curl_slist_append(list, "Content-Type: application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		//Le decimos a CURL que trabaje con credentials.
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen("grant_type=client_credentials"));
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");

		//Le decimos a curl que cuando haya que escribir llame a myCallback
		//y que use al string readString como user data.
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, myCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readString);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK)
		{
			err.type = CURL_EASY_PERF_ERR;
			err.detail = "curl_easy_perform() failed: " + curl_easy_strerror(res);
			//Hacemos un clean up de curl antes de salir.
			curl_easy_cleanup(curl)
		}
		else
		{
			// Si no hubo errores hago un clean up antes de realizar un nuevo query.
			curl_easy_cleanup(curl);

			//Si el request de CURL fue exitoso entonces twitter devuelve un JSON
			//Abajo busco el token en el JSON para luego acceder a los twits.
			json answer = json::parse(readString);

			try
			{
				//Tratamos de acceder al campo acces_token del JSON
				std::string aux = answer["access_token"];
				token = aux;
			}
			catch (std::exception& e)
			{
				//Si hubo algun error, se muestra el error que devuelve la libreria
				err.detail = e.what();
				err.type = TOKEN_ACCESS_ERR;
			}
		}
	}
	else
	{
		err.type = CURL_START_ERR;
		err.detail = "Cannot download tweets. Unable to start cURL";
	}
}

/*getTwits:
Recibe cantidad de twits para solicitar al servidor
En caso de recibir 0, se pide la cantidad por defecto que envie el servidor*/
bool twUser::getTwits(const char *user,unsigned int cant)
{
	//query = "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=lanacion&count=10";

}

void twUser::parseTwits(void)
{

}

twUser::~twUser()
{
}
