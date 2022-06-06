#include <iostream>
using namespace std;
  
using namespace std;
  
class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;
        Term* next;
        Term(int exp, int coeff, Term* n) :exponent(exp), coefficient(coeff), next(n) {};
        friend class Polynomial;
    private:
        Term(Term* t) :exponent(t->exponent), coefficient(t->coefficient), next(t->next) {
            cout << "copy constructor on TERM!!!" << flush;
        };
    };
public:
    Polynomial() :head(nullptr), vathmos(0), size(0) {};
    Polynomial(const Polynomial& p) { copy(p); };
    ~Polynomial() { clear(); };
  
    Polynomial& operator = (const Polynomial& p) { clear(); copy(p); return *this; };
  
    void addTerm(int expon, int coeff);
    double evaluate(double x);
  
    friend Polynomial operator+ (const Polynomial& p, const Polynomial& q);
    friend Polynomial operator* (const Polynomial& p, const Polynomial& q);
  
    friend ostream& operator<<(ostream& out, const Polynomial& p);
  
private:
  
    int vathmos, size;
    Term* head;
  
    int getExpOfTerm(Term* t) const {
        return t->exponent;
    }
    int getCoefOfTerm(Term* t) const {
        return t->coefficient;
    }
    Term* multiplayTerms(Term* q, Term* p) {
        Term* multiTerm;
        if (p->exponent == 0)
            multiTerm = new Term(q->exponent, p->coefficient * q->coefficient, nullptr);
        else if (q->exponent == 0)
            multiTerm = new Term(p->exponent, p->coefficient * q->coefficient, nullptr);
        else
            multiTerm = new Term(p->exponent + q->exponent, p->coefficient * q->coefficient, nullptr);
        return multiTerm;
    }
  
  
    void copy(const Polynomial& p) {
        head = p.head;
        vathmos = p.vathmos;
        size = p.size;
        for (Term* currenTerm = head; currenTerm != nullptr; currenTerm = currenTerm->next) {
            addTerm(currenTerm->exponent, currenTerm->coefficient);
        }
    }
  
    void clear() {
        Term* l = head;
        vathmos = 0;
        size = 0;
        while (l != nullptr) {
            Term* q = l;
            l = l->next;
            delete q;
        }
    }
  
    void removeTerm(int exp) {
        Term* temp = head;
        Term* prev = nullptr;
        if (head == nullptr)
            return;
        else {
            if (head->exponent == exp) {
                head = head->next;
                delete temp;
            }
            else {
                for (temp = head; temp->next != nullptr && temp->exponent != exp; temp = temp->next) {
                    prev = temp;
                }
                if (temp->exponent == exp) {
                    prev->next = temp->next;
                    delete temp;
                }
                else  return;
            }
            --size;
        }
    }
  
    Polynomial* addTermsOfPol(const Polynomial& q) {
        for (Term* currentTerm = q.head; currentTerm != nullptr; currentTerm = currentTerm->next) {
            this->addTerm(currentTerm->exponent, currentTerm->coefficient);
        }
        return this;
    };
  
    Polynomial* multiplyTermsOfPol(const Polynomial& p, const Polynomial& q) {
  
        Polynomial* multiPol = new Polynomial();
        for (Polynomial::Term* qterm = p.head; qterm != nullptr; qterm = qterm->next) {
            for (Polynomial::Term* pterm = q.head; pterm != nullptr; pterm = pterm->next) {
                Polynomial::Term* mTerm = multiPol->multiplayTerms(qterm, pterm);
                int exp = multiPol->getExpOfTerm(mTerm);
                int coef = multiPol->getCoefOfTerm(mTerm);
                multiPol->addTerm(exp, coef);
            }
        }
        return multiPol;
    };
  
    ostream& printTerms(ostream& out) {
        if (this->head == nullptr) {
            return out << "0" << flush;
        }
        for (Polynomial::Term* t = this->head; t != nullptr; t = t->next) {
            if (t == this->head) {
                if (t->exponent > 1)
                    if (t->coefficient > 1)
                        out << t->coefficient << "x^" << t->exponent << flush;
                    else if (t->coefficient < -1)
                        out << "- " << -t->coefficient << "x^" << t->exponent << flush;
                    else if (t->coefficient == -1)
                        out << "- x^" << t->exponent << flush;
                    else if (t->coefficient == 1)
                        out << "x^" << t->exponent << flush;
                    else
                        out << "" << flush;
                else if (t->exponent == 1) {
                    if (t->coefficient > 1)
                        out << t->coefficient << "x" << flush;
                    else if (t->coefficient < -1)
                        out << "- " << t->coefficient << "x" << flush;
                    else if (t->coefficient == -1)
                        out << "- x" << flush;
                    else if (t->coefficient == 1)
                        out << "x" << flush;
                    else
                        out << "" << flush;
                }
                else {
                    if (t->coefficient > 0)
                        out << t->coefficient << flush;
                    else if (t->coefficient < 0)
                        out << "- " << -t->coefficient << flush;
                    else
                        out << "" << flush;
                }
            }
            else {
                if (t->exponent > 1)
                    if (t->coefficient > 1)
                        out << " + " << t->coefficient << "x^" << t->exponent << flush;
                    else if (t->coefficient < -1)
                        out << " - " << -t->coefficient << "x^" << t->exponent << flush;
                    else if (t->coefficient == -1)
                        out << " - x^" << t->exponent << flush;
                    else if (t->coefficient == 1)
                        out << " + x^" << t->exponent << flush;
                    else
                        out << "" << flush;
                else if (t->exponent == 1) {
                    if (t->coefficient > 1)
                        out << " + " << t->coefficient << "x" << flush;
                    else if (t->coefficient < -1)
                        out << " - " << -t->coefficient << "x" << flush;
                    else if (t->coefficient == -1)
                        out << " - x" << flush;
                    else if (t->coefficient == 1)
                        out << " + x" << flush;
                    else
                        out << "" << flush;
                }
                else {
                    if (t->coefficient > 0)
                        out << " + " << t->coefficient << flush;
                    else if (t->coefficient < 0)
                        out << " - " << -t->coefficient << flush;
                    else
                        out << "" << flush;
                }
            }
        }
        return out;
    }
};
  
void Polynomial::addTerm(int expon, int coeff)
{
    if (coeff == 0 || expon < 0) return;
    Term* newTerm = new Term(expon, coeff, nullptr);
    Term* temp = head;
    if (expon > vathmos)
        vathmos = expon;
    if (head == nullptr) {
        newTerm->next = nullptr;
        head = newTerm;
        ++size;
        return;
    }
    if (expon > head->exponent) {
        newTerm->next = head;
        head = newTerm;
        ++size;
        return;
    }
    if (expon == head->exponent) {
        if (head->coefficient == -newTerm->coefficient)
            removeTerm(head->exponent);
        return;
    }
    while (temp->next != nullptr) {
        if (expon == temp->exponent) {
            if (temp->coefficient == -newTerm->coefficient)
                removeTerm(temp->exponent);
            return;
        }
        if (expon > temp->next->exponent) {
            newTerm->next = temp->next;
            temp->next = newTerm;
            return;
        }
        temp = temp->next;
    }
    if (newTerm->exponent == temp->exponent) {
        if (temp->coefficient == -newTerm->coefficient)
            removeTerm(temp->exponent);
        return;
    }
    else {
        newTerm->next = nullptr;
        temp->next = newTerm;
        ++size;
    }
    return;
}
  
double Polynomial::evaluate(double x)
{
    double result = 0;
    for (Term* currentTerm = head; currentTerm != nullptr; currentTerm = currentTerm->next) {
        double valOfExp = 1;
        if (currentTerm->exponent == 0)
            valOfExp = 1;
        else {
            for (int i = 0; i < currentTerm->exponent; ++i) {
                valOfExp *= x;
            }
        }
        result += (currentTerm->coefficient) * valOfExp;
    }
    return result;
}
  
Polynomial operator+(const Polynomial& p, const Polynomial& q)
{
    Polynomial* addPol = new Polynomial(p);
    addPol->addTermsOfPol(q);
    return *addPol;
}
Polynomial operator*(const Polynomial& p, const Polynomial& q)
{
    Polynomial* multiPol = new Polynomial();
    multiPol->multiplyTermsOfPol(p, q);
    return Polynomial();
}
ostream& operator<<(ostream& out, const Polynomial& p)
{
    Polynomial* printPol = new Polynomial(p);
    return printPol->printTerms(out);
}
