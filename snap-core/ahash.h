
////////////////////////////////////////////////
// Attribute Hash-Table
// TODO: Currently, never resizes.  To do so, must overwrite most
// THash functions whenever a new TDat is added
template<class TKey, class TDat, class THashFunc = TDefaultHashFunc<TKey> >
class TAHash: public THash<TKey, TDat, THashFunc>{
private:
  int ListSize;
  THash<TKey, TVec<TDat> > AttrLists;
  void ResizeAttr();
public:
  typedef THashKeyDatI<TKey, TDat> TIter;
  TAHash():
    AttrLists(){
      ListSize = 1;}
  TAHash(const TAHash& AHash):
    AttrLists(AHash.AttrLists){
      ListSize = 1;}

  bool AddAttr(const TKey& Attribute);
  void DelAttr(const TKey& Attribute){AttrLists.DelIfKey(Attribute);}

  TDat& AddAttrDat(const TKey& Key, const TDat& Dat, const TKey& Attribute){
    return AttrLists.GetDat(Attribute)[GetKeyId(Key)] = Dat;};
  TDat& GetAttrDat(const TKey& Key, const TKey& Attribute){
    return AttrLists.GetDat(Attribute)[GetKeyId(Key)];}

  void DelAttrKey(const TKey& Attribute){
    AttrLists.MarkDelKey(Attribute);}
  
  TVec<TKey> GetAttrs();
};

template<class TKey, class TDat, class THashFunc>
void TAHash<TKey, TDat, THashFunc>::ResizeAttr(){
  ListSize *= 2;
  TIter Iterator = AttrLists.BegI();
  while (!Iterator.IsEnd()) {
    Iterator.GetDat().Gen(ListSize);
    Iterator++;
  } 
}

template<class TKey, class TDat, class THashFunc>
bool TAHash<TKey, TDat, THashFunc>::AddAttr(const TKey& Attribute){
  if (AttrLists.IsKey(Attribute)){return false;}

  AttrLists.AddKey(Attribute);
  AttrLists.AddDat(Attribute, TVec<TDat>(ListSize));
  
  return true;
}
