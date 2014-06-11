#include "DTO.h"

//define constructors and function implementations here
// The constructor
// Purpose: To initialize needed variables
// Parameters: None
// Returns: None
// Pre-conditions: None
// Post-conditions: Specific variables initialized
// -----------------------------------------------------------------
Patron::Patron(string fName, string lName,bool isAdult)
{
  patronFirstName = fName;
  patronLastName = lName;
  adult = isAdult;
  bookList = new vector<int>();
  idAssigned = false;
}

// The GetBookList Method
// Purpose: To see which books a certain patron has checked out
// Parameters: 1 int (int patronID)
// Returns: string
// Pre-conditions: Valid parameter values in order to see which books a certain patron has checked out
// Post-conditions: A list of books that the patron currecntly has checked out is returned to the user interface
// -----------------------------------------------------------------
vector<int> Patron::GetBookList()
{
	return bookList;
}

void Patron::AssignPatronId(int id)
{
  if(!idAssigned)
    {
      idAssigned = true;
      patronID = id;
    }
  else
    {
      throw runtime_error("Can't reassign user id");
    }
}

// The Patron Destructor
// Purpose: To delete a patron
// Parameters: None
// Returns: None
// Pre-conditions: Patron that we are attempting to delete exist and can be deleted
// Post-conditions: Correct patron deleted
// -----------------------------------------------------------------
Patron::~Patron()
{

}
