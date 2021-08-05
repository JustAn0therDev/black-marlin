// Enum class with HTTP Status Codes.
enum class StatusCode 
{
	// Resource created in the server.
	kCreated = 201,
	// Nothing returned in the response body but the headers might be useful (or not).
	kNoContent = 204,
	// Client sent a request with bad syntax.
	kBadRequest = 400,
	// An expection was caught and the client must know it happened.
	kInternalServerError = 500
};
